#pragma once

#include "SFML//Network.hpp"
#include <iostream>
#include <string>
#include <vector>

#define SAFE_DEL(x) delete x; x = nullptr;


class ServerClientData
{
public:
	ServerClientData();
	ServerClientData(std::string IP_User, unsigned short port_user, std::string name_user);
	~ServerClientData();

	const void set_IP_user(const std::string& IP);
	const std::string* get_IP_user();

	const void set_port(const unsigned short port);
	const unsigned short get_port();

	const void set_name_user(const std::string& userName);
	const std::string* get_name_user();


	bool operator==(const sf::IpAddress &otherClient);//determinating if new message is from old client
	bool operator==(const unsigned short &otherPort);//for testing on the same computer

private:
	std::string* _IP_user;
	unsigned short _port_user;
	std::string* _name_user;
};
