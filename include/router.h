/**
 * @file router.h
 *
 * @author Avis
 * */

#ifndef JF_FRAMEWORK_ROUTER_H
#define JF_FRAMEWORK_ROUTER_H

#include <export.h>
#include <http.h>
#include <stdint.h>

#define MAX_MIDDLEWARE 32
#define MAX_ROUTES 128

typedef int (*middleware_t)(const HttpRequest* request, HttpResponse* response); // return 0 = stop, 1 = continue
typedef void (*route_handler_t)(const HttpRequest* request, HttpResponse* response);

typedef struct {
    char method[8];
    char path[256];
    route_handler_t handler;
} Route;

typedef struct {
    Route routes[MAX_ROUTES];
    uint32_t routeCount;
    middleware_t middleware[MAX_MIDDLEWARE];
    uint32_t middlewareCount;
} Router;

JF_EXPORT void jf_RouterDestroy(Router* router);
JF_EXPORT uint32_t jf_RouterAdd(Router* router, const char* method, const char* path, route_handler_t handler);
uint32_t jf_RouterDispatch(Router* router, HttpRequest* httpRequest, HttpResponse* httpResponse);
JF_EXPORT Router* jf_CreateRouter(void);
JF_EXPORT uint32_t jf_RouterUse(Router* router, middleware_t middleware);

#endif
