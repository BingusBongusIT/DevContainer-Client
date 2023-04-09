//
// Created by colllijo on 09.04.2023.
//

#include "../header/Socket.hpp"

Socket::Socket()
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(m_socket == -1)
    {
        // Error creating the socket
        delete this;
    }
}

bool Socket::Bind(const char *bindingIp, int port)
{
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = port;
    inet_pton(AF_INET, bindingIp, &m_addr.sin_addr);

    if(bind(m_socket, (sockaddr*)&m_addr, sizeof(m_addr)) == -1)
    {
        // Error binding the socket to the ip and port
        return false;
    }
    std::cout << "Socket bound" << std::endl;
    return true;
}

bool Socket::Listen(int maxConnections) const
{
    if(listen(m_socket, maxConnections) == -1)
    {
        // Error starting the listening on the socket
        return false;
    }
    std::cout << "Socket listening" << std::endl;
    return true;
}

bool Socket::Accept(Socket* incomingSocket)
{
    socklen_t socketLength = sizeof(m_addr);

    m_socket = accept(incomingSocket->m_socket, (sockaddr*)&m_addr, &socketLength);
    if(m_socket == -1)
    {
        // Error accepting the incoming connection
        return false;
    }

    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    memset(host, 0, NI_MAXHOST);
    memset(serv, 0, NI_MAXSERV);

    int nameInfo = getnameinfo((sockaddr*)&m_addr, sizeof(m_addr), host, NI_MAXHOST, serv, NI_MAXSERV, 0);
    if(nameInfo)
    {
        std::cout << host << " connected on " << serv << std::endl;
    }
    else
    {
        inet_ntop(AF_INET, &m_addr.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on " << ntohs(m_addr.sin_port) << std::endl;
    }

    return true;
}

bool Socket::Connect(const char* serverIp, int port)
{
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);
    inet_pton(AF_INET, serverIp, &m_addr.sin_addr);

    if (connect(m_socket, (sockaddr*)&m_addr, sizeof(m_addr)) == -1)
    {
        // Error connecting to the server
        return false;
    }
    return true;
}

int Socket::Send(const void *buffer, int bufferSize) const
{
    return send(m_socket, buffer, bufferSize, 0);
}

int Socket::Receive(void *buffer, int bufferSize) const
{
    memset(buffer, 0, bufferSize);
    return recv(m_socket, buffer, bufferSize, 0);
}

void Socket::Close() const
{
    close(m_socket);
}

Socket::~Socket()
{
    close(m_socket);
    m_addr = {};
}