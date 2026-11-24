#include <iostream>
#include <ctime>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(1313);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));

    listen(serverSocket, 5);

    cout << "Daytime server on port 1313" << endl;

    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);

        time_t currentTime = time(nullptr);
        char* timeText = ctime(&currentTime);

        send(clientSocket, timeText, strlen(timeText), 0);

        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}