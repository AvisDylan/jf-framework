#include <http.h>
#include <router.h>
#include <server.h>
#include <stdio.h>
#include <string.h>

void homeHandler(const HttpRequest*, HttpResponse* httpResponse) { // Response without helper
    httpResponse->response = HTTP_OK; // Set status

    const char* body = "Hello, World!";

    httpResponse->body = strdup(body); // Set body
    httpResponse->bodyCapacity = strlen(body); // Set body capacity

    strncpy(httpResponse->contentType, "text/plain", sizeof(httpResponse->contentType) - 1); // Set content type

    httpResponse->contentType[sizeof(httpResponse->contentType) - 1] = '\0'; // Null terminate string
    httpResponse->contentLength = strlen(body); // Set content length
}

void storeHandler(const HttpRequest*, HttpResponse* httpResponse) { // Response with string helper
    jf_SendString(httpResponse, "Welcome to Store", HTTP_OK); // Send string
}

void aboutHandler(const HttpRequest*, HttpResponse* httpResponse) { // Reponse with HTML helper
    jf_SendHTMLFile(httpResponse, "resources/about.html", HTTP_OK); // Send HTML file
}

void apiHandler(const HttpRequest* httpRequest, HttpResponse* httpResponse) { // API that prints name
    const char* name = jf_GetParameter(httpRequest, "name"); // Get value of parameter name

    printf("Hello, %s", name); // Print name

    jf_SendJson(httpResponse, "{\"ok\": true}", HTTP_OK); // Send JSON response
}

int main(void) {
    Router* router = jf_CreateRouter(); // Create router

    if (!router)
        return 1; // Return 1 if router fails to create

    jf_RouterAdd(router, "GET", "/", homeHandler); // Add a GET route on path / handled by homeHandler
    jf_RouterAdd(router, "GET", "/store", storeHandler); // Add a GET route on path /store handled by storeHandler
    jf_RouterAdd(router, "GET", "/about", aboutHandler); // Add a GET route on path /about handled by aboutHandler
    jf_RouterAdd(router, "POST", "/api/{name}",
                 apiHandler); // Add a POST route on path /api/{name} handled by apiHandler

    Server* server = jf_CreateServer(8080); // Create server with port 8080

    if (!server)
        return 1; // Return 1 if server fails to create

    jf_ServerUseRouter(server, router); // Bind router to server

    if (jf_Listen(server) != 0) // Opens listening socket
        return 1; // Return 1 if failure to open listening socket

    printf("Server started!\n");

    jf_RunServer(server); // Run accept loop

    // Cleanup router and server
    jf_DestroyServer(server);
    jf_RouterDestroy(router);

    return 0;
}
