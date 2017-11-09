#include "Server.h"
#include "ServerClientData.h"	// forward declare

#include <thread>


// cTor
Server::Server() : _port_incoming(50000), _port_connected(50001), _data_client(nullptr)
{
	_socket_server_incoming = new sf::UdpSocket();
	_socket_server_connected = new sf::UdpSocket();
	_socket_server_incoming->bind(_port_incoming);
	_socket_server_connected->bind(_port_connected);

	_IP_server = new std::string(sf::IpAddress::getLocalAddress().toString());

	_data_client = new ServerClientData();
}


// dTor
Server::~Server()
{
	SAFE_DEL(_socket_server_incoming);
	SAFE_DEL(_IP_server);
	SAFE_DEL(_data_client);
	SAFE_DEL(_socket_server_connected);
}


// set IP server
const void Server::set_IP_server(const std::string& IP)
{
	if(_IP_server != nullptr)
		delete _IP_server;

	_IP_server = new std::string(IP);
}


// get IP server
const std::string* Server::get_IP_server()
{
	return _IP_server;
}


// set port
const void Server::set_port(const unsigned short port)
{
	_port_incoming = port;
}


// get port
const unsigned short Server::get_port()
{
	return _port_incoming;
}


// get client data
const ServerClientData* Server::get_data_client()
{
	return _data_client;
}


// incoming client
const void Server::incoming_client()
{
	char in[1024];
	std::size_t received = 0;
	sf::IpAddress clientIP;
	unsigned short clientPort;

	while (true)
	{
		_socket_server_incoming->receive(in, sizeof(in), received, clientIP, clientPort);
		unsigned int clientID = clientIP.toInteger() + clientPort;

		if (_server_clients.find(clientID) == _server_clients.end())
		{
			std::string tempStr(in);
			ServerClientData* newClient = new ServerClientData(clientIP.toString(), clientPort, tempStr);

			_server_clients[clientID] = newClient;
			std::cout << tempStr << " has connected " << std::endl;

			// send new port to client
			std::string switchPort = "50001";
			_socket_server_incoming->send(switchPort.c_str(), sizeof(switchPort), clientIP, clientPort);
		}
	}
}


// connected clients
const void Server::connected_clients()
{
	char in[1024];
	std::size_t received = 0;
	sf::IpAddress client_IP;
	unsigned short client_port;

	while (true)
	{
		//recieve
		_socket_server_connected->receive(in, sizeof(in), received, client_IP, client_port);
		std::string message = in;
		ParseData tmp_data = parse_function(message);
		std::string command_name = tmp_data.command;
		command_name.erase(0,1);

		unsigned int client_ID = client_IP.toInteger() + client_port;

		// whisper
		std::cout << command_name;
		if (tmp_data.command.size() != 0)
		{
			for (auto& i : _server_clients)
			{
				if (*i.second->get_name_user() == command_name)
				{
					std::string message = "\n" + tmp_data.username + " whispers: " + tmp_data.message;
					_socket_server_connected->send(message.c_str(), sizeof(message), *i.second->get_IP_user(), i.second->get_port());
					break;
				}
			}
		}
		else // all
		{
			for (auto& i : _server_clients)
			{
				if (i.first != client_ID)
				{
					std::string message = "\n" + tmp_data.username + " says: " + tmp_data.message;
					_socket_server_connected->send(message.c_str(), sizeof(in), *i.second->get_IP_user(), i.second->get_port());
				}
			}
		}
	}
}

const ParseData Server::parse_function(const std::string& message)
{
	ParseData parseData;

	size_t counter = 1;
	size_t other_counter = -1;
	size_t message_index = 1;


	for (int j = 0; j < 3; j++)
	{ 
		switch (counter)
		{
		// user name
		case 1:
			for (int i = message_index; i < message.size(); i++)
			{
				other_counter++;

				if (message[i] != '^')
				{
					parseData.username += message[i];
				}
				else
				{
					message_index = other_counter + 2;
					counter++;
					break;
				}
			}
			
			break;

		// command
		case 2:
			for (int i = message_index; i < message.size(); i++)
			{
				other_counter++;

				if (message[i] != '^')
				{
					parseData.command += message[i];
				}
				else
				{
					message_index = other_counter + 2;
					counter++;
					break;
				}
			}
			
			break;

		// message
		case 3:
			for (int i = message_index; i < message.size(); i++)
				parseData.message += message[i];

			break;

		// default
		default:
			std::cout << "Error in parse_function() switch" << std::endl;
			break;
		}
	}

	return parseData;
}


// orbit
void Server::orbit()
{
	// recieve
	char in[1024];
	std::size_t received = 0;
	sf::IpAddress client_IP;
	unsigned short client_port;

	while (true)
	{
		std::thread incoming_thread(&Server::incoming_client, this);
		std::thread connected_thread(&Server::connected_clients, this);
		incoming_thread.join();
		connected_thread.join();
	}
}


// print debug
void Server::print_debug()
{
	//std::cout << _data_client->get_IP_user()->toString() << std::endl;
	//std::cout << _port_server << std::endl;
	//std::cout << *_IP_server << std::endl;
}
