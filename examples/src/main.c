#include <http.h>
#include <router.h>
#include <server.h>
#include <stdio.h>
#include <string.h>

void homeHandler(const HttpRequest* httpRequest, HttpResponse* httpResponse) {
    (void) httpRequest;

    httpResponse->response = HTTP_OK; // Set status

    const char* body = "Hello, World!";

    httpResponse->body = strdup(body); // Set body
    httpResponse->bodyCapacity = strlen(body); // Set body capacity

    strncpy(httpResponse->contentType, "text/plain", sizeof(httpResponse->contentType) - 1); // Set content type

    httpResponse->contentType[sizeof(httpResponse->contentType) - 1] = '\0'; // Null terminate string
}

int main(void) {
    Router* router = jf_CreateRouter(); // Create router

    if (!router)
        return 1; // Return 1 if router fails to create

    jf_RouterAdd(router, "GET", "/", homeHandler); // Add a GET route on path / handled by homeHandler

    Server* server = jf_CreateServer(8080); // Create server with port 8080

    if (!server)
        return 1; // Return 1 if server fails to create

    jf_ServerUseRouter(server, router); // Bind router to server

    if (jf_Listen(server) != 0) // Opens listening socket
        return 1; // Return 1 if failure to open listening socket

    printf("Server started!");

    jf_RunServer(server); // Run accept loop

    // Cleanup router and server
    jf_DestroyServer(server);
    jf_RouterDestroy(router);

    return 0;
}
