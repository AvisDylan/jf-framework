/**
 * @file server.c
 *
 * @author Avis
 *
 * HTTP server
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <http.h>
#include <netinet/in.h>
#include <server.h>
#include <stddef.h>
#include <sys/socket.h>
#include "router.h"

/**
 * @author Avis
 *
 * @brief Creates server struct
 *
 * @return NULL on failure and pointer to server on sucess
 */
Server* jf_CreateServer(int32_t port) {
    Server* server = calloc(1, sizeof(Server));

    if (!server)
        return NULL;

    server->port = port;
    server->sockfd = -1;
    server->clientfd = -1;

    memset(&server->address, 0, sizeof(server->address));

    server->address.sin_family = AF_INET; // IPV4 TODO add IPV6 after with dual stacking
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(port);

    return server;
}

/**
 * @author victor
 *
 * @brief Opens listening socket
 */
uint32_t jf_Listen(Server* server) {
    if (server == NULL) {
        return 1;
    }
    server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->sockfd < 0) {
        return 2;
    }


    struct sockaddr_in* addr = &server->address;

    if (bind(server->sockfd, (struct sockaddr*) addr, sizeof(*addr)) < 0) {
        close(server->sockfd);
        server->sockfd = -1;
        return 3;
    }

    if (listen(server->sockfd, 5) < 0) {
        close(server->sockfd);
        server->sockfd = -1;
        return 4;
    }
    return 0;
}

/**
 * @author victor
 *
 * @brief Accept loop
 *
 * @param server Pointer to server struct
 *
 * @return Return code
 */
uint32_t jf_RunServer(Server* server) {
    if (server == NULL) {
        return 1;
    }
    if (server->sockfd < 0) {
        return 2;
    }
    while (1) {
        server->clientfd = accept(server->sockfd, NULL, NULL);
        if (server->clientfd < 0) {
            return 3;
        }
        jf_HandleClient(server);
        close(server->clientfd);

        server->clientfd = -1;
    }
}

/**
 * @authors Victor, Avis
 *
 * @brief
 *
 * @return Returns 1 on failure, 2 on success
 */
uint32_t jf_HandleClient(Server* server) {
    char buffer[8192];

    size_t recieved = recv(server->sockfd, buffer, sizeof(buffer), 0);

    if (recieved < 0) {
        return 1;
    }

    buffer[recieved] = '\0';

    printf("Received: %s\n", buffer); // TODO remove for prod

    HttpRequest httpRequest;
    HttpResponse httpResponse;

    jf_InitHttpResponse(&httpResponse);

    if (!jf_ParseHttpRequest(&httpRequest, buffer, recieved)) {
        httpResponse.response = HTTP_BAD_REQUEST;

        strncpy(httpResponse.reason, "Bad Request", sizeof(httpResponse.reason) - 1);

        httpResponse.reason[sizeof(httpResponse.reason) - 1] = '\0';

        jf_SendHttpResponse(server->clientfd, &httpResponse);

        return 1;
    }

    if (!server->router) {
        perror("Server has no router");

        httpResponse.response = HTTP_NOT_FOUND;
        strncpy(httpResponse.reason, "Not Found", sizeof(httpResponse.reason) - 1);
        httpResponse.reason[sizeof(httpResponse.reason) - 1] = '\0';
        httpResponse.contentLength = 0;
    } else
        jf_RouterDispatch(server->router, &httpRequest, &httpResponse);

    jf_SendHttpResponse(server->clientfd, &httpResponse);

    if (!httpResponse.body)
        free(httpResponse.body);

    return 0;
}

/**
 * @author Avis
 *
 * @brief Closes server and frees resources
 *
 * @param server Pointer to server struct
 * */
void jf_DestroyServer(Server* server) {
    if (!server)
        return;

    if (server->sockfd >= 0)
        close(server->sockfd);

    if (server->clientfd >= 0)
        close(server->clientfd);

    free(server);
}

/**
 * @author Avis
 *
 * @brief Binds router to server
 * */
void jf_ServerUseRouter(Server* server, Router* router) {
    if (!server)
        return;

    server->router = router;
}
