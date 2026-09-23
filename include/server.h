/**
 * @file server.h
 *
 * @author Avis
 * */

#ifndef JF_FRAMEWORK_SERVER_H
#define JF_FRAMEWORK_SERVER_H

#include <export.h>
#include <netinet/in.h>
#include <router.h>
#include <stdint.h>

typedef struct {
    int clientfd;
    int sockfd;
    int port;
    struct sockaddr_in6 address;
    Router* router;
} Server;

JF_EXPORT Server* jf_CreateServer(int32_t port);

JF_EXPORT uint32_t jf_Listen(Server* server);

JF_EXPORT uint32_t jf_RunServer(Server* server); // was jf_RunSever changed i changed name

uint32_t jf_HandleClient(Server* server);

JF_EXPORT void jf_ServerUseRouter(Server* server, Router* router);

JF_EXPORT void jf_DestroyServer(Server* server);

#endif
