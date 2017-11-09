#pragma once

#include "SFML//Network.hpp"
#include <iostream>
#include <string>
#include <vector>

#define SAFE_DEL(x) delete x; x = nullptr;


class Client
{
public:
	Client();
	~Client();

	const void send_message();
	const void recieve_message();

	const std::string* message_function(const std::string& message);

	const void set_IP_user(const std::string& IP);
	const std::string* get_IP_user();

	const void set_IP_server(const std::string& IP);
	const std::string* get_IP_server();

	const void set_port(const unsigned short port);
	const unsigned short get_port();

	const void set_name_user(const std::string& userName);
	const std::string* get_name_user();

	const void set_pass_user(const std::string& userPass);
	const std::string* get_pass_user();

	const void orbit();

private:
	sf::UdpSocket* _socket_user;
	std::string* _IP_user;
	std::string* _IP_server;
	unsigned short _port_user;
	unsigned short _port_server;

	size_t _counter;

	std::string* _name_user;
	std::string* _pass_user;

	std::vector<std::string*> _message_log_user;

	enum CONNECT { dial, online }
	_connect_setting = CONNECT::dial;
};
