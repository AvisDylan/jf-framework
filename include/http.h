/**
 * @file http.h
 *
 * @author Avis
 * */

#ifndef JF_FRAMEWORK_HTTP_H
#define JF_FRAMEWORK_HTTP_H

#include <stddef.h>
#include <stdint.h>

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
    uint32_t response;
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

uint32_t jf_ParseHttpRequest(const HttpRequest* httpRequest);

#endif
