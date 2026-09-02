/**
 * @file router.c
 *
 * @author Avis
 * */

#include <router.h>

#include <string.h>

static Route routes[MAX_ROUTES];
static uint32_t routeCount = 0;

/**
 * @author Victor
 *
 * @brief
 */
uint32_t jf_RouterAdd(const char* method, const char* path, const char* router, route_handler_t handler){
    if (router == NULL || method == NULL || path == NULL) {
        return 0;
    }
    if(router->routeCount >= MAX_ROUTES) {
        return 2;
    }

    Route *route =
        &router->routes[routerCount];

    strncpy(
        route->method,
        method,
        sizeof(route->method) -1
        );
}   route->method[sizeof(route->method)-1] = '\0' ;


/**
 * @author Victor
 *
 * @brief
 */
void jf_CreateRouter(void){

}
