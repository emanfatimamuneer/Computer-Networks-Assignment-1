// thread_server.cpp - Tutorial 8: one thread per client
#include <atomic>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include "net.hpp"

static std::mutex g_log;
static std::atomic<int> g_active{0};

static void serve_client(net::Socket client, std::string who) {
    int now = ++g_active;
    {
        std::lock_guard<std::mutex> lock(g_log);
        std::cout << who << " connected. Active clients: " << now << std::endl;
    }
    char buf[1024];
    for (;;) {
        long long n = net::recv_some(client.get(), buf, sizeof buf);
        if (n <= 0) break;
        if (!net::send_all(client.get(), buf, static_cast<size_t>(n))) break;
    }
    int left = --g_active;
    std::lock_guard<std::mutex> lock(g_log);
    std::cout << who << " disconnected. Active clients: " << left << std::endl;
}

int main(int argc, char** argv) {
    const char* port = (argc > 1) ? argv[1] : "5000";
    try {
        net::Runtime runtime;
        net::Socket listener = net::tcp_listen(port);
        std::cout << "Thread server on port " << port << std::endl;
        for (;;) {
            sockaddr_storage peer{};
            sock_len peer_len = sizeof peer;
            net::Socket client(accept(listener.get(),
                reinterpret_cast<sockaddr*>(&peer), &peer_len));
            if (!client.valid()) continue;
            std::string who = net::peer_name(
                reinterpret_cast<sockaddr*>(&peer), peer_len);
            std::thread(serve_client, std::move(client), who).detach();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
