/**
 * @file router.h
 *
 * @author Avis
 * */

#ifndef JF_FRAMEWORK_ROUTER_H
#define JF_FRAMEWOR_ROUTER_H

#include <http.h>
#include <stdint.h>

#define MAX_ROUTES 128

typedef void (*route_handler_t)(const HttpRequest* request, HttpResponse* response);

typedef struct {
    char method[8];
    char path[256];
    route_handler_t handler;
} Route;

typedef struct {
    Route routes[MAX_ROUTES];
    uint32_t routeCount;
} Router;

void jf_RouterDestroy(Router* router);
uint32_t jf_RouterAdd(Router* router, const char* method, const char* path, route_handler_t handler);
uint32_t jf_RouterDispatch(Router* router, const HttpRequest* httpRequest, HttpResponse* httpResponse);
Router* jf_CreateRouter(void);

#endif
