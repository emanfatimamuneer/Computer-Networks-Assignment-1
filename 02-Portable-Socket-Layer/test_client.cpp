
#include <iostream>
#include <string>
#include "net.hpp"

int main() {
    try {
        net::Runtime runtime;

        // Connect to the server
        net::Socket client = net::tcp_connect("127.0.0.1", "6000");

        std::cout << "Connected to server!" << std::endl;

        // Send a message
        std::string message = "Hello from client!";

        if (!net::send_all(
            client.get(), message.data(), message.size()
        )) {
            throw std::runtime_error("Send failed");
        }

        std::cout << "Message sent!" << std::endl;

        // Receive the server's reply
        char buffer[1024];

        long long received = net::recv_some(
            client.get(), buffer, sizeof(buffer)
        );

        if (received > 0) {
            std::string reply(buffer, received);
            std::cout << "Server says: " << reply << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
