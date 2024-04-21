#include <iostream>
#include <tchar.h>
#include <WinSock2.h>

// For converting network routing to binary
// TO-dos: Do network routing to binary manually without a lib
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

    cout << "hello world" << endl;

    SOCKET CreateSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (CreateSocket == INVALID_SOCKET) {
        cout << "Socket Creation - FAILED" << endl;
        return 1;
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

    return 0;
}