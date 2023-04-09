#include <iostream>
#include <cstring>

#include "../header/Socket.hpp"

int main()
{
    const char* serverIp = "127.0.0.1";
    int port = 42024;

    Socket* socket = new Socket();
    if(!socket->Connect(serverIp, port))
    {
        std::cerr << "Couln't connect to the server." << std::endl;
        return 1;
    }

    int bufferSize = 4096;
    char buffer[bufferSize];
    std::string userInput;

    do {
        std::cout << "> ";
        getline(std::cin, userInput);


        int sendRes = socket->Send(userInput.c_str(), userInput.size() + 1);
        if (sendRes == -1)
        {
            std::cout << "Could not send to server! Whoops!\n";
            continue;
        }

        memset(buffer, 0, bufferSize);
        int bytesReceived = socket->Receive(buffer, bufferSize);
        if (bytesReceived == -1)
        {
            std::cout << "There was an error getting response from server\n";
        }
        else
        {
            std::cout << "SERVER> " << std::string(buffer, bytesReceived) << "\n";
        }
    } while(true);

    socket->Close();
    delete socket;

    return 0;
}