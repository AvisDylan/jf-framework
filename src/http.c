/**
 * @file http.c
 *
 * @author Avis
 * */

#include <http.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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
    // this code is by avis
}
