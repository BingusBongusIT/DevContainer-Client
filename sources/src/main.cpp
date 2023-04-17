#include <iostream>
#include <thread>

#include "../header/Socket.hpp"
#include "../header/Client.hpp"

void PrintLogo();

int main()
{
	Client client;
	if(!client.Initialize())
	{
		std::cerr << "Error starting the client" << std::endl;
		return 1;
	}

	PrintLogo();
	std::cout << "Welcome to CChat!" << std::endl;

	std::string userInput;
	while(client.m_running)
	{
		std::getline(std::cin, userInput);
		client.HandleInput(&userInput);
	}

    return 0;
}


void PrintLogo()
{
	std::cout << "\t                              \t" << std::endl;
	std::cout << "\t   ______________          __ \t" << std::endl;
	std::cout << "\t  / ____/ ____/ /_  ____ _/ /_\t" << std::endl;
	std::cout << "\t / /   / /   / __ \\/ __ `/ __/\t" << std::endl;
	std::cout << "\t/ /___/ /___/ / / / /_/ / /_  \t" << std::endl;
	std::cout << "\t\\____/\\____/_/ /_/\\__,_/\\__/  \t" << std::endl;
	std::cout << "\t                              \t" << std::endl;
	std::cout << "\t                              \t" << std::endl;
}