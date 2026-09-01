/**
 * @file server.h
 *
 * @author Avis
 * */

#ifndef JF_FRAMEWORK_SERVER_H
#define JF_FRAMEWORK_SERVER_H

#include <netinet/in.h>
#include <stdint.h>

typedef struct {
    int32_t sockfd;
    int32_t port;
    struct sockaddr_in address;
} Server;

Server* jf_CreateServer(int32_t port);

uint32_t jf_Listen(Server* server);

uint32_t jf_RunSever(Server* server);

uint32_t jf_HandleClient(Server* server);

void jf_DestroyServer(Server* server);

#endif
