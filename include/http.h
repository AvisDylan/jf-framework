/**
 * @file http.h
 *
 * @author Avis
 * */

#ifndef JF_FRAMEWORK_HTTP_H
#define JF_FRAMEWORK_HTTP_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    HTTP_CONTINUE = 100,
    HTTP_SWITCHING_PROTOCOLS = 101,
    HTTP_PROCESSING = 102,

    HTTP_OK = 200,
    HTTP_CREATED = 201,
    HTTP_ACCEPTED = 202,
    HTTP_NO_CONTENT = 204,
    HTTP_PARTIAL_CONTENT = 206,

    HTTP_MULTIPLE_CHOICES = 300,
    HTTP_MOVED_PERMANENTLY = 301,
    HTTP_FOUND = 302,
    HTTP_SEE_OTHER = 303,
    HTTP_NOT_MODIFIED = 304,
    HTTP_TEMPORARY_REDIRECT = 307,
    HTTP_PERMANENT_REDIRECT = 308,

    HTTP_BAD_REQUEST = 400,
    HTTP_UNAUTHORIZED = 401,
    HTTP_FORBIDDEN = 403,
    HTTP_NOT_FOUND = 404,
    HTTP_METHOD_NOT_ALLOWED = 405,
    HTTP_REQUEST_TIMEOUT = 408,
    HTTP_CONFLICT = 409,
    HTTP_GONE = 410,
    HTTP_LENGTH_REQUIRED = 411,
    HTTP_PAYLOAD_TOO_LARGE = 413,
    HTTP_UNSUPPORTED_MEDIA_TYPE = 415,
    HTTP_TOO_MANY_REQUESTS = 429,

    HTTP_INTERNAL_SERVER_ERROR = 500,
    HTTP_NOT_IMPLEMENTED = 501,
    HTTP_BAD_GATEWAY = 502,
    HTTP_SERVICE_UNAVAILABLE = 503,
    HTTP_GATEWAY_TIMEOUT = 504,
    HTTP_VERSION_NOT_SUPPORTED = 505
} HttpStatus;

// https://www.rfc-editor.org/info/rfc2616/
typedef struct {
    char method[8];
    char path[256];
    char version[16];
    char query[256];
    char host[256];
    char contentType[128];
    size_t contentLength;
    struct {
        char name[64];
        char value[256];
    } headers[32];
    uint32_t headerCount;
    const char* body;
    size_t bodyLength;
    struct {
        char key[32];
        char value[128];
    } params[32];
    uint32_t paramCount;
} HttpRequest;

typedef struct {
    HttpStatus response;
    char reason[64];
    char contentType[128];
    size_t contentLength;
    struct {
        char name[64];
        char value[256];
    } headers[32];
    uint32_t headerCount;
    char* body;
    size_t bodyCapacity;
} HttpResponse;

uint32_t jf_ParseHttpRequest(HttpRequest* httpRequest, const char* buffer, size_t length);
void jf_InitHttpResponse(HttpResponse* response);
uint32_t jf_SendHttpResponse(int32_t sockfd, const HttpResponse* response);

#endif
