//
// Created by colllijo on 12.04.2023.
//

#ifndef CC_CLIENT_CLIENT_HPP
#define CC_CLIENT_CLIENT_HPP

#include <cstring>
#include <vector>
#include <thread>

#include "Socket.hpp"

class Client {
public:
	bool m_running;
	bool m_connectedToServer;

	bool Initialize();
	void HandleInput(std::string* input);
	void Delete();
private:
	const std::string m_commandString = "/";
	const std::vector<std::string> m_commands = {
			"help",			// 0
			"connect",		// 1
			"disconnect",	// 2
			"quit",			// 3
			"login",		// 4
			"logout",		// 5
			"register",		// 6
			"msg"			// 7
	};

	Socket* m_socket;
	std::thread m_serverListener;

	int m_bufferSize;
	char* m_buffer;

	void ReceiveMessages();

	void ListCommands();
	void ConnectToServer(const std::string& serverAddress);
	void Login();
	void Logout();
	void Register();
	void StartChat(std::string client);
};


#endif //CC_CLIENT_CLIENT_HPP
