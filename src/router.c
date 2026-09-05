/**
 * @file router.c
 *
 * @author Avis
 * */

#include <router.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http.h"

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

/* Finds route by method and name */
static const Route* jf_RouterMatch(Router* router, const char* method, const char* path) {
    for (uint32_t i = 0; i < router->routeCount; i++) {
        if (strcmp(router->routes[i].method, method) == 0 && strcmp(router->routes[i].method, method) == 0)
            return &router->routes[i];
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
uint32_t jf_RouterDispatch(Router* router, const HttpRequest* httpRequest, HttpResponse* httpResponse) {
    if (!router || !httpRequest || !httpResponse)
        return 0;

    const Route* route = jf_RouterMatch(router, httpRequest->method, httpRequest->path);

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
