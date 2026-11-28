
#include <iostream>
#include <string>
#include "net.hpp"

int main() {
    try {
        net::Runtime runtime;

        // Start listening on port 6000
        net::Socket server = net::tcp_listen("6000");

        std::cout << "Server listening on port 6000..." << std::endl;

        // Accept an incoming client connection
        net::Socket client(accept(server.get(), nullptr, nullptr));

        if (!client.valid())
            throw std::runtime_error("Accept failed");

        std::cout << "Client connected!" << std::endl;

        // Receive a message from the client
        char buffer[1024];

        long long received = net::recv_some(
            client.get(), buffer, sizeof(buffer)
        );

        if (received > 0) {
            std::string message(buffer, received);

            std::cout << "Client says: " << message << std::endl;

            // Send a reply
            std::string reply = "Hello from server!";

            if (!net::send_all(
                client.get(), reply.data(), reply.size()
            )) {
                throw std::runtime_error("Send failed");
            }

            std::cout << "Reply sent!" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
