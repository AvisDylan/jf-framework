/**
 * @file logger.h
 *
 * @author Avis
 *
 * Logs connections
 * */

#ifndef JF_FRAMEWORK_LOGGER_H
#define JF_FRAMEWORK_LOGGER_H

#include <export.h>
#include <http.h>

JF_EXPORT int jf_Logger(const HttpRequest* httpRequest, HttpResponse* httpResponse);

#endif
