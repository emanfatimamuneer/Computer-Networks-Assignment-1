
#include <iostream>
#include "net.hpp"

int main() {
    try {
        net::Runtime runtime;

        std::cout << "Portable Socket Layer initialized successfully!"
                  << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
