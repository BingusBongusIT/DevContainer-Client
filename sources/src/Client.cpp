//
// Created by colllijo on 12.04.2023.
//

#include "../header/Client.hpp"

bool Client::Initialize()
{
	m_socket = new Socket();

	m_bufferSize = 4096;
	m_buffer = new char[m_bufferSize];

	m_running = true;
	m_connectedToServer = false;

	return true;
}

void Client::HandleInput(std::string* input)
{
	// Check if the input is a command
	if (input->starts_with(m_commandString))
	{
		std::string command = input->substr(m_commandString.size());
		std::string arguments;

		//Check if command has arguments
		std::string::size_type endOfCommand = command.find(' ', 0);
		if (endOfCommand != std::string::npos)
		{
			arguments = command.substr(endOfCommand + 1);
			command = command.substr(0, endOfCommand);
		}

		// Check if command exists
		auto commandIterator = std::find(m_commands.begin(), m_commands.end(), command);
		if (commandIterator != m_commands.end())
		{
			std::string message;

			// Turn the command into it's index for use in the switch
			int commandIndex = commandIterator - m_commands.begin();
			switch (commandIndex) {
				case 0: // /help
					ListCommands();
					break;
				case 1: // /connect
					ConnectToServer(arguments);
					break;
				case 2: // /disconnect
					if(m_connectedToServer)
					{
						m_socket->Close();
						delete m_socket;
						m_socket = new Socket();

						m_connectedToServer = false;
						m_serverListener.detach();
						std::cout << "Disconnected from the server" << std::endl;
					}
					else
					{
						std::cout << "Not connected to a server" << std::endl;
					}
					break;
				case 3: // /quit
					std::cout << "Quiting CChat" << std::endl;
					Delete();
					break;
				case 4: // /login
					if (m_connectedToServer)
					{
						Login();
					}
					else
					{
						std::cout << "Please first connect to a server before logging in." << std::endl;
					}
					break;
				case 5: // /logout
					if (m_connectedToServer)
					{
						Logout();
					}
					else
					{
						std::cout << "Please first connect to a server before logging in." << std::endl;
					}
					break;
				case 6: // /register
					if (m_connectedToServer)
					{
						Register();
					}
					else
					{
						std::cout << "Please first connect to a server before logging in." << std::endl;
					}
					break;
				case 7: // /msg
					if (m_connectedToServer)
					{
						StartChat(arguments);
					}
					else
					{
						std::cout << "Please first connect to a server before logging in." << std::endl;
					}
					break;
				default:
					break;
			}
		}
		else
		{
			std::cout << "command not found use " << m_commandString << "help to see a list of commands" << std::endl;
		}
	}
	else
	{
		if(m_connectedToServer)
		{
			std::string messageString = "msg: " + *input;
			m_socket->Send(messageString.c_str(), messageString.size() + 1);
		}
	}
}

void Client::ListCommands()
{
	std::cout << "CChat Help:" << std::endl;
	std::cout << "\t\t --- Basic Commands --- " << std::endl;
	std::cout << "\t" << m_commandString << "help\t\t\t\t - show this help menu" << std::endl;
	std::cout << "\t" << m_commandString << "connect <server-ip>:<port>\t - connect to a CChat server at <server-ip>:<port>" << std::endl;
	std::cout << "\t" << m_commandString << "disconnect\t\t\t - close the connection from the server" << std::endl;
	std::cout << "\t" << m_commandString << "quit\t\t\t\t - exit CChat" << std::endl;
	std::cout << "\t\t --- Server Commands --- " << std::endl;
	std::cout << "\t" << m_commandString << "login\t\t\t\t - start the login process" << std::endl;
	std::cout << "\t" << m_commandString << "logout\t\t\t\t - logout the current user" << std::endl;
	std::cout << "\t" << m_commandString << "register\t\t\t - create a new user" << std::endl;
	std::cout << "\t" << m_commandString << "msg <client>\t\t\t - start a chat with <client>" << std::endl;
}

void Client::ConnectToServer(const std::string& serverAddress)
{
	if(m_connectedToServer)
	{
		std::cout << "Already connected to a server please disconnect first, before connecting to a new server." << std::endl;
		return;
	}

	std::string ip;
	int port = 0;

	//Split serverAddress into ip and port
	std::string::size_type separator = serverAddress.find(':', 0);
	if (separator != std::string::npos)
	{
		ip = serverAddress.substr(0, separator);
		port = std::stoi(serverAddress.substr(separator + 1));
	}

    if(!m_socket->Connect(ip.c_str(), port))
    {
        std::cerr << "Couldn't connect to the server.\nMake sure to enter the server address as <ip>:<port>." << std::endl;
		return;
	}

	std::cout << "Successfully connected to the server" << std::endl;
	m_serverListener = std::thread(&Client::ReceiveMessages, this);
	m_connectedToServer = true;
}

void Client::Login()
{
	std::string username;
	std::string password;

	std::cout << "Username: ";
	getline(std::cin, username);
	password = std::string(getpass("Password: "));

	std::string loginString = "command: login|" + username + ":" + password;
	m_socket->Send(loginString.c_str(), loginString.size() + 1);
}

void Client::Logout()
{
	std::string logoutString = "command: logout";
	m_socket->Send(logoutString.c_str(), logoutString.size() + 1);
}

void Client::Register()
{
	std::string username;
	std::string password;

	std::cout << "Username: ";
	getline(std::cin, username);
	password = std::string(getpass("Password: "));

	if(password != getpass("Retype Password: "))
	{
		std::cerr << "Passwords do not match!" << std::endl;
		return;
	}

	std::string registerString = "command: register|" + username + ":" + password;
	m_socket->Send(registerString.c_str(), registerString.size() + 1);
}

void Client::StartChat(std::string client)
{
	std::string messageClientString = "command: msg| " + client;
	m_socket->Send(messageClientString.c_str(), messageClientString.size() + 1);
}

void Client::ReceiveMessages()
{
	while(m_connectedToServer)
	{
		memset(m_buffer, 0, m_bufferSize);
		int bytesReceived = m_socket->Receive(m_buffer, m_bufferSize);
		if (bytesReceived == -1)
		{
			std::cout << "There was an error getting a response from the server" << std::endl;
		}
		else if (bytesReceived == 0)
		{
			m_socket->Close();
			delete m_socket;
			m_socket = new Socket();

			m_connectedToServer = false;
			std::cout << "Server disconnected" << std::endl;
			break;
		}
		else
		{
			std::cout << "> " << std::string(m_buffer, bytesReceived) << std::endl;
		}
	}
}

void Client::Delete()
{
	m_running = false;

	m_socket->Close();
	delete m_socket;

	m_bufferSize = 0;
	delete m_buffer;
}