// Created by Avis on 01/09/2026

#ifndef JF_FRAMEWORK_ROUTER_H
#define JF_FRAMEWOR_ROUTER_H

#include <stdint.h>
#include <http.h>

#define MAX_ROUTES 128

typedef void (*route_handler_t)(const HttpRequest* request, HttpResponse* response);

typedef struct{
    char method[8];
    char path[256];
    route_handler_t handler;
} Route;

void jf_CreateRouter(void);

void jf_RouterAdd(const char* method, const char* path, route_handler_t handler);

uint32_t jf_RouterRoute(const HttpRequest* request, HttpResponse* response);

#endif