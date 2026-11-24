
// select_server.cpp - Select-based TCP echo server

#include <iostream>
#include <vector>
#include <utility>
#include "net.hpp"

int main(int argc, char** argv) {

    const char* port = (argc > 1) ? argv[1] : "5000";

    try {
        net::Runtime runtime;

        net::Socket listener = net::tcp_listen(port);

        std::cout << "Select Server started on port "
                  << port << std::endl;

        std::vector<net::Socket> clients;

        char buffer[1024];

        while (true) {

            fd_set readfds;
            FD_ZERO(&readfds);

            // Monitor the listening socket.
            FD_SET(listener.get(), &readfds);

            // Monitor all connected clients.
            socket_t max_fd = listener.get();

            for (const auto& client : clients) {
                FD_SET(client.get(), &readfds);

                if (client.get() > max_fd)
                    max_fd = client.get();
            }

            // Wait until at least one socket becomes readable.
            int activity = select(
                static_cast<int>(max_fd) + 1,
                &readfds,
                nullptr,
                nullptr,
                nullptr
            );

            if (activity < 0) {
                std::cerr << "Select failed!" << std::endl;
                break;
            }

            // Check whether a new client is connecting.
            if (FD_ISSET(listener.get(), &readfds)) {

                net::Socket newClient(
                    accept(listener.get(), nullptr, nullptr)
                );

                if (newClient.valid()) {

                    if (clients.size() < FD_SETSIZE - 1) {

                        std::cout << "New client connected!"
                                  << std::endl;

                        clients.push_back(std::move(newClient));

                    } else {
                        std::cout << "Maximum clients reached."
                                  << std::endl;
                    }
                }
            }

            // Check existing clients.
            for (size_t i = 0; i < clients.size();) {

                if (FD_ISSET(clients[i].get(), &readfds)) {

                    long long bytes = net::recv_some(
                        clients[i].get(),
                        buffer,
                        sizeof(buffer)
                    );

                    // Client disconnected or an error occurred.
                    if (bytes <= 0) {

                        std::cout << "Client disconnected."
                                  << std::endl;

                        clients.erase(clients.begin() + i);
                        continue;
                    }

                    std::cout << "Received: ";

                    std::cout.write(buffer, bytes);
                    std::cout << std::endl;

                    // Echo the received data to this client.
                    if (!net::send_all(
                            clients[i].get(),
                            buffer,
                            static_cast<size_t>(bytes)
                        )) {

                        std::cout << "Send failed. Client removed."
                                  << std::endl;

                        clients.erase(clients.begin() + i);
                        continue;
                    }
                }

                ++i;
            }
        }

    } catch (const std::exception& e) {

        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
