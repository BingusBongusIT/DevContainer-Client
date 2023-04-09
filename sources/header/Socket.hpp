//
// Created by colllijo on 09.04.2023.
//

#ifndef CC_CLIENT_SOCKET_HPP
#define CC_CLIENT_SOCKET_HPP

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class Socket {
public:
    int m_socket;

    Socket();
    ~Socket();

    bool Bind(const char* bindingIp, int port);
    bool Listen(int maxConnections = SOMAXCONN) const;
    bool Connect(const char* serverIp, int port);
    bool Accept(Socket* incomingSocket);
    int Send(const void* buffer, int bufferSize) const;
    int Receive(void* buffer, int bufferSize) const;
    void Close() const;
private:
    sockaddr_in m_addr{};
};

#endif //CC_CLIENT_SOCKET_HPP
