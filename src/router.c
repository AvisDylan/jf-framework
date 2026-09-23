// Created by Avis on 23/09/2026

/**
 * @file router.c
 *
 * @author Avis
 * */

#include <router.h>

#include <http.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @author Avis
 *
 * @brief Cleans up router object
 * */
void jf_RouterDestroy(Router* router) {
    if (!router)
        return;

    free(router);
}

/**
 * @author Avis
 *
 * @brief Adds route to router
 *
 * @return Returns 0 on failure, 1 on success, and 2 if max routes in exceeded
 * */
uint32_t jf_RouterAdd(Router* router, const char* method, const char* path, route_handler_t handler) {
    if (!router || !method || !path || !handler)
        return 0;

    if (router->routeCount >= MAX_ROUTES)
        return 2;

    Route* route = &router->routes[router->routeCount];

    strncpy(route->method, method, sizeof(route->method) - 1);

    route->method[sizeof(route->method) - 1] = '\0';

    strncpy(route->path, path, sizeof(route->path) - 1);

    route->path[sizeof(route->path) - 1] = '\0';
    route->handler = handler;

    router->routeCount++;

    return 1;
}

/**
 * @author Avis
 *
 * @brief Allocates and creates router object
 *
 * @return Pointer to router, NULL on failure
 * */
Router* jf_CreateRouter(void) {
    Router* router = calloc(1, sizeof(Router));

    if (!router)
        return NULL;

    return router;
}

/* Finds next segment of path; path is path cursor */
static size_t jf_RouterNextSegment(const char** path, const char** segment) {
    const char* current = *path;

    while (*current == '/') {
        current++;
    }

    if (*current == '\0')
        return 0;

    *segment = current;

    while (*current != '\0' && *current != '/') {
        current++;
    }

    *path = current;

    return (size_t) (current - *segment);
}

/* Compares route pattern to request segment and checks for pattern segment placeholder {placeholder} */
static uint32_t jf_RouterMatchSegment(const char* routeSegemnt, size_t routeSegmentLength, const char* requestSegment,
                                      size_t requestSegmentLength, HttpRequest* httpRequest) {
    if (routeSegmentLength >= 2 && routeSegemnt[0] == '{' &&
        routeSegemnt[routeSegmentLength - 1] == '}') { // place holder found
        if (httpRequest->paramCount >= 32)
            return 0;

        size_t keyLength = routeSegmentLength - 2;

        if (keyLength >= sizeof(httpRequest->params[0].key))
            keyLength = sizeof(httpRequest->params[0].key) - 1;

        memcpy(httpRequest->params[httpRequest->paramCount].key, routeSegemnt + 1, keyLength);
        httpRequest->params[httpRequest->paramCount].key[keyLength] = '\0';

        if (requestSegmentLength >= sizeof(httpRequest->params[0].value))
            requestSegmentLength = sizeof(httpRequest->params[0].value) - 1;

        memcpy(httpRequest->params[httpRequest->paramCount].value, requestSegment, requestSegmentLength);
        httpRequest->params[httpRequest->paramCount].value[requestSegmentLength] = '\0';

        httpRequest->paramCount++;

        return 1;
    }

    return routeSegmentLength == requestSegmentLength && memcmp(routeSegemnt, requestSegment, routeSegmentLength) == 0;
}

static uint32_t jf_RouterMatchPath(const Route* route, const char* requestPath, HttpRequest* httpRequest) {
    const char* routePath = route->path;
    const char* routeRequest = requestPath;

    httpRequest->paramCount = 0;

    for (;;) {
        const char* routeSegment;

        size_t routeSegmentLength = jf_RouterNextSegment(&routePath, &routeSegment);

        const char* requestSegment;

        size_t requestSegmentLength = jf_RouterNextSegment(&requestPath, &requestSegment);

        if (routeSegmentLength == 0 && requestSegmentLength == 0)
            return 1;

        if (routeSegmentLength == 0 || requestSegmentLength == 0)
            return 0;

        if (!jf_RouterMatchSegment(routeSegment, routeSegmentLength, requestSegment, requestSegmentLength,
                                   httpRequest)) {
            return 0;
        }
    }
}

/* Finds route with request */
static const Route* jf_RouterMatch(Router* router, HttpRequest* httpRequest) {
    for (uint32_t i = 0; i < router->routeCount; i++) {
        const Route* route = &router->routes[i];

        if (strcmp(route->method, httpRequest->method) != 0)
            continue;

        if (jf_RouterMatchPath(route, httpRequest->path, httpRequest))
            return route;
    }

    return NULL;
}

/**
 * @author Avis
 *
 * @brief Handles routes
 *
 * @return Returns 0 on error, 1 on success
 * */
uint32_t jf_RouterDispatch(Router* router, HttpRequest* httpRequest, HttpResponse* httpResponse) {
    if (!router || !httpRequest || !httpResponse)
        return 0;

    // run middleware
    for (uint32_t i = 0; i < router->middlewareCount; i++) {
        int cont = router->middleware[i](httpRequest, httpResponse);

        if (!cont)
            return 1;
    }

    const Route* route = jf_RouterMatch(router, httpRequest);

    if (!route) {
        httpResponse->response = HTTP_NOT_FOUND; // 404

        strncpy(httpResponse->reason, "Not Found", sizeof(httpResponse->reason) - 1);

        httpResponse->reason[sizeof(httpResponse->reason) - 1] = '\0';
        httpResponse->contentLength = 0;

        return 0;
    }

    route->handler(httpRequest, httpResponse);

    return 1;
}

/**
 * @author Avis
 *
 * @brief Adds middleware to router
 *
 * @return 0 on failure, 1 on success, 2 if max middleware is exceeded
 * */
uint32_t jf_RouterUse(Router* router, middleware_t middleware) {
    if (!router || !middleware)
        return 0;

    if (router->middlewareCount >= MAX_MIDDLEWARE)
        return 2;

    router->middleware[router->middlewareCount++] = middleware;
    return 1;
}
