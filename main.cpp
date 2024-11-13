#include <iostream>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/http_listener.h>  // Include this for http_listener

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace web::http::experimental::listener;  // HTTP listener

void handle_get(http_request request) {
    // Create a JSON object to send in the response
    json::value response_data;
    response_data[U("message")] = json::value::string(U("Hello from cpprestsdk!"));

    // Set the response code to OK (200) and send the response as JSON
    request.reply(status_codes::OK, response_data);
}

void start_http_server(){
    // Define the URL where the server will listen
    uri_builder uri(U("http://localhost:8080"));

    // Create an HTTP listener at the specified URL
    http_listener listener(uri.to_uri());

    // Set the function to handle GET requests
    listener.support(methods::GET, handle_get);

    // Open the listener and start the server
    try {
        listener
            .open()
            .then([&listener](){ std::cout << listener.uri().to_string() << std::endl; })
            .wait();
    } catch (const std::exception& e) {
        std::cerr << "Error starting server: " << e.what() << std::endl;
    }

    // Keep the server running until terminated by the user
    std::string line;
    std::getline(std::cin, line);
}

void fetch_request(){
    // Create HTTP client
    http_client client(U("https://jsonplaceholder.typicode.com"));

    // Send GET request
    client.request(methods::GET, U("/todos/1"))
        .then([](http_response response) {
            if (response.status_code() == status_codes::OK) {
                return response.extract_json();  // Extract JSON from the response
            }
            return pplx::task_from_result(json::value()); // Return empty JSON if not OK
        })
        .then([](json::value jsonResponse) {
            std::cout << "Response JSON: " << jsonResponse.serialize() << std::endl;
        })
        .wait(); // Wait for the async request to finish
}

int main() {
    
    fetch_request();
    start_http_server();

    return 0;
}
