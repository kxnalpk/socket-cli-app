#include <iostream>
#include <tchar.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;
#pragma comment(lib, "ws2_32.lib")

bool SocketInitialization() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

int main() {
    string SocketStatus = SocketInitialization() ? "SUCCESS" : "FAILED";
    cout << "Socket connection - " << SocketStatus << endl;

    if (SocketStatus == "FAILED") {
        cout << "Socket initialization failed. Exiting program." << endl;
        return 1;
    }

    SOCKET CreateSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (CreateSocket == INVALID_SOCKET) {
        cout << "Socket Creation - FAILED" << endl;
        return 1;
    }
    else {
        cout << "Socket Creation - SUCCESS" << endl;
    }

    sockaddr_in RoutingAddress;

    RoutingAddress.sin_family = AF_INET;
    RoutingAddress.sin_port = htons(69690);

    if (InetPton(AF_INET, _T("0.0.0.0"), &RoutingAddress.sin_addr) != 1) {
        cout << "Routing Address Convetion - FAILED" << endl;
        closesocket(CreateSocket);

        WSACleanup();
        return 1;
    }

    if(bind(CreateSocket, reinterpret_cast<sockaddr*>(&RoutingAddress), sizeof(RoutingAddress)) == SOCKET_ERROR) {
        closesocket(CreateSocket);
        WSACleanup();
        return 1;
    }

    if (listen(CreateSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "Socket Listening - FAILED" << endl;
        closesocket(CreateSocket);
        WSACleanup();
        return 1;
    }
    else {
        cout << "Server Listening - SUCCESS [69690]" << endl;
    }

    SOCKET ClientSocket = accept(CreateSocket, nullptr, nullptr);
    if (ClientSocket == INVALID_SOCKET) {
        cout << "Client Socket - INVALID" << endl;
    }

    char buffer[4096];
    int NtGot = recv(ClientSocket, buffer, sizeof(buffer), 0);

    string message(buffer, NtGot);
    cout << "Client Side:" << message << endl;

    closesocket(ClientSocket);
    closesocket(CreateSocket);

    WSACleanup();
    return 0;
}