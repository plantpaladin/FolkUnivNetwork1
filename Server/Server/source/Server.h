#pragma once

#include "SFML//Network.hpp"
#include <iostream>
#include <string>
#include <vector>

class ServerClientData;

#define SAFE_DEL(x) delete x; x = nullptr;


struct ParseData
{
	std::string username;
	std::string command;
	std::string message;
};


class Server
{
public:
	Server();
	~Server();

	const void set_IP_server(const std::string& IP);
	const std::string* get_IP_server();

	const void set_port(const unsigned short port);
	const unsigned short get_port();
	const ServerClientData* get_data_client();

	const void incoming_client();
	const void connected_clients();

	const ParseData parse_function(const std::string& message);

	void orbit();

	void print_debug();

private:
	sf::UdpSocket* _socket_server_connected;
	sf::UdpSocket* _socket_server_incoming;
	std::string* _IP_server;
	unsigned short _port_incoming;
	unsigned short _port_connected;

	ServerClientData* _data_client;
	std::map<INT32, ServerClientData*> _server_clients;
	
};
