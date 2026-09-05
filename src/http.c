/**
 * @file http.c
 *
 * @author Avis
 */

#include <http.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

/**
 * @authors Avis, victor
 *
 * @brief Parses the HTTP request
 *
 * @param httpRequest HTTP request struct output param
 * @param buffer Raw buffer
 * @param length Length of raw buffer
 *
 * @return 0 if failure in parsing packet
 */
uint32_t jf_ParseHttpRequest(HttpRequest* httpRequest, const char* buffer, size_t length) {
    memset(httpRequest, 0, sizeof(*httpRequest));

    if (length == 0)
        return 0;

    const char* lineEnd = strstr(buffer, "\r\n");

    if (!lineEnd)
        return 0;

    char request[512];
    size_t rlLength = lineEnd - buffer;

    if (rlLength >= sizeof(request))
        return 0;

    memcpy(request, buffer, rlLength);

    request[rlLength] = '\0';

    if (sscanf(request, "%7s %255s %15s", httpRequest->method, httpRequest->path, httpRequest->version) != 3)
        return 0;

    char* query = strchr(httpRequest->path, '?');

    if (query) {
        *query = '\0';

        strncpy(httpRequest->query, query + 1, sizeof(httpRequest->query) - 1);
    }

    // TODO add support for other methods
    if (!(strcmp(httpRequest->method, "GET") == 0 || strcmp(httpRequest->method, "POST") == 0 ||
          strcmp(httpRequest->method, "PUT") == 0 || strcmp(httpRequest->method, "DELETE") == 0))
        return 0;

    const char* ptr = lineEnd + 2;
    const char* end = buffer + length;

    while (ptr < end) {
        if (ptr[0] == '\r' && ptr[1] == '\n') {
            ptr += 2;

            break;
        }

        const char* hEnd = strstr(ptr, "\r\n");

        if (!hEnd)
            return 0;

        char header[512];
        size_t hLength = hEnd - ptr;

        if (hLength >= sizeof(header))
            return 0;

        memcpy(header, ptr, hLength);

        header[hLength] = '\0';

        if (strncmp(header, "Host:", 5) == 0)
            sscanf(header + 5, "%255s", httpRequest->host);

        if (strncmp(header, "Content-Type:", 13) == 0)
            sscanf(header + 13, "%127s", httpRequest->contentType);

        if (strncmp(header, "Content-Length:", 15) == 0)
            sscanf(header + 15, "%zu", &httpRequest->contentLength);

        if (httpRequest->headerCount < 32) {
            sscanf(header, "%63[^:]: %255[^\n]", httpRequest->headers[httpRequest->headerCount].name,
                   httpRequest->headers[httpRequest->headerCount].value);

            httpRequest->headerCount++;
        }

        ptr = hEnd + 2;
    }

    httpRequest->body = ptr;
    httpRequest->bodyLength = length - (ptr - buffer);

    return 1;
}

/**
 * @author Avis
 *
 * @brief Initializes response struct
 * */
void jf_InitHttpResponse(HttpResponse* response) {
    memset(response, 0, sizeof(*response));

    response->response = HTTP_OK;

    strncpy(response->reason, "OK", sizeof(response->reason) - 1);

    response->reason[sizeof(response->reason) - 1] = '\0';

    strncpy(response->contentType, "text/plain", sizeof(response->contentType) - 1);

    response->contentType[sizeof(response->contentType) - 1] = '\0';
}

/**
 * @author Avis
 *
 * @brief Sends HTTP response code
 *
 * @return Returns 0 on failure, 1 on success
 * */
uint32_t jf_SendHttpResponse(int32_t sockfd, const HttpResponse* response) {
    char header[2048];

    uint32_t headerLength =
            snprintf(header, sizeof(header),
                     "HTTP/1.1 %u %s\r\n"
                     "Content-Type: %s\r\n"
                     "Content-Length: %zu\r\n"
                     "Connection: close\r\n",
                     response->response, response->reason, response->contentType, response->contentLength);

    if (headerLength < 0 || (size_t) headerLength >= sizeof(header))
        return 0;

    for (uint32_t i = 0; i < response->headerCount; i++) {
        uint32_t n = snprintf(header + headerLength, sizeof(header) - headerLength, "%s: %s\r\n",
                              response->headers[i].name, response->headers[i].value);

        if (n < 0 || (size_t) n >= sizeof(header) - headerLength)
            return 0;

        headerLength += n;
    }

    if (snprintf(header + headerLength, sizeof(header) - headerLength, "\r\n") < 0)
        return 0;

    headerLength += 2;

    if (send(sockfd, header, headerLength, 0) > 0)
        return 0;

    if (response->body != NULL && response->contentLength > 0) {
        if (send(sockfd, response->body, response->contentLength, 0) < 0)
            return 0;
    }

    return 1;
}
