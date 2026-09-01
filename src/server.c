// Created by Avis on 01/09/2026

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <server.h>
#include <stddef.h>

/**
 * @file server.c
 * 
 * @author Avis
 * 
 * @brief Creates server struct
 * 
 * @return NULL on failure and pointer to server on sucess 
 */
Server* jf_CreateServer(int32_t port){
    Server* server = malloc(sizeof(Server));
  
    if(!server)
        return NULL;

    server->port = port;
    server->sockfd = -1;

    memset(&server->address, 0, sizeof(server->address));
    
    server->address.sin_family = AF_INET; // IPV4 TODO add IPV6 after
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(port);

    return server;
}

/**
 * @file server.c
 * 
 * @author victor
 * 
 * @brief Opens listening socket
 */
uint32_t jf_Listen(Server* server){
    if (server == NULL)
        {
        return 1;
        }
    server->sockfd = socket(
        AF_INET, 
        SOCK_STREAM, 
        0
    );
    if (server->sockfd < 0)
        {
        return 2;
        }

        
    struct sockaddr_in* addr = &server->address;
    
    if (bind(server->sockfd, (struct sockaddr*) addr, sizeof(*addr)) < 0)
        {
            close(server->sockfd);
            server->sockfd = -1;
        return 3;
        }
    
    if (listen(server->sockfd, 5) < 0)
        {
            close(server->sockfd);
            server->sockfd = -1;
        return 4;
        }
    return 0;
}
   
/**
 * @file server.c
 * 
 * @author victor
 * 
 * @brief Accept loop
 * 
 * @param server Pointer to server struct
 * 
 * @return Return code
 */
uint32_t jf_RunSever(Server* server){
    if (server == NULL)
        {
            return 1;

        }
    if (server->sockfd < 0){
        return 2;
        }
    while(1)
        {
            server->sockfd = accept(server->sockfd, NULL, NULL);
            if (server->sockfd < 0)
                {
                    return 3;
                }
            jf_HandleClient(server);
            close(server->sockfd);
        }
}

/**
 * @file server.c
 * 
 * @author Victor
 * 
 * @brief
 * 
 * @return
 */
uint32_t jf_HandleClient(Server* server){
    char buffer[8192];
    
    size_t recieved = recv(server->sockfd, buffer, sizeof(buffer), 0);
    if (recieved < 0)
    {
        return 1;
    }
    buffer[recieved] = '\0';
    printf("Received: %s\n", buffer);

    const char* response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 13\r\n"
        "connection: close\r\n"
        "\r\n"
        "Hello, World!";

}

/**
 * @file server.c
 * 
 * @author Avis
 * 
 * @brief Closes server and frees resources
 * 
 * @param server Pointer to server struct 
 * */
void jf_DestroyServer(Server* server){
    if(!server)
        return;

    if(server->sockfd >= 0)
        close(server->sockfd);

    free(server);
}