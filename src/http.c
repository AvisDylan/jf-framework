/**
 * @file http.c
 *
 * @author Avis
 * */

#include <http.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/**
 * @author victor
 *
 * @brief Parses the HTTP request
 *
 * @param httpRequest HTTP request struct
 *
 * @return
 */
uint32_t jf_ParseHttpRequest(const HttpRequest* httpRequest) {
    // this code is by avis
    if (httpRequest->body == NULL)
        goto DROP_PACKET;

    if (!(strcmp(httpRequest->method, "GET") == 0 || strcmp(httpRequest->method, "POST") == 0 ||
          strcmp(httpRequest->method, "PUT") == 0 || strcmp(httpRequest->method, "DELETE") == 0))
        goto DROP_PACKET;

    // TODO add checks

    // handle

    return 0; // 0 is temp change

DROP_PACKET:
    // drop packet

    return 0; // 0 is temp change
}
