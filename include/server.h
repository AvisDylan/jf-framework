/**
 * @file server.h
 *
 * @author Avis
 * */

#ifndef JF_FRAMEWORK_SERVER_H
#define JF_FRAMEWORK_SERVER_H

#include <netinet/in.h>
#include <stdint.h>
#include "router.h"

typedef struct {
    int32_t clientfd;
    int32_t sockfd;
    int32_t port;
    struct sockaddr_in address;
    Router* router;
} Server;

Server* jf_CreateServer(int32_t port);

uint32_t jf_Listen(Server* server);

uint32_t jf_RunServer(Server* server); // was jf_RunSever changed i changed name

uint32_t jf_HandleClient(Server* server);

void jf_ServerUseRouter(Server* server, Router* router);

void jf_DestroyServer(Server* server);

#endif
