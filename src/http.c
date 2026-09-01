// Created by Avis on 01/09/2026

#include <http.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

/**
 * @file http.c
 * 
 * @author victor
 * 
 * @return
 */
uint32_t jf_ParseHttpRequest(const HttpRequest* httpRequest){
    //code by avis }
    if(httpRequest->body == NULL)
        goto DROP_PACKET;

    if(!(strcmp(httpRequest->method, "GET") == 0 ||
         strcmp(httpRequest->method, "POST") == 0 ||
         strcmp(httpRequest->method, "PUT") == 0 || 
         strcmp(httpRequest->method, "DELETE") == 0))
        goto DROP_PACKET;

    // TODO add checks

    // handle

    return 0; //0 is temp change
DROP_PACKET:
    // drop packet 

    return 0; //0 is temp change
}