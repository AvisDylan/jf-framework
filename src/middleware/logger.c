/**
 * @file logger.c
 *
 * @author Avis
 *
 *
 * */

#include <http.h>
#include <middleware/logger.h>
#include <stddef.h>
#include <stdio.h>

/**
 * @author Avis
 *
 * @brief Logs incoming requests
 * */
JF_EXPORT int jf_Logger(const HttpRequest* httpRequest, HttpResponse* httpResponse) {
    printf("%s %s %s", httpRequest->method, httpRequest->path, httpRequest->host);

    return 1;
}
