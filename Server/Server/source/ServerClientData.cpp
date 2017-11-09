#include "ServerClientData.h"


// cTor
ServerClientData::ServerClientData() : _IP_user(nullptr), _port_user(0), _name_user(nullptr)
{
	
}

ServerClientData::ServerClientData(std::string IP_User, unsigned short port_user, std::string name_user)
{
	_IP_user = new std::string(IP_User);
	_port_user = port_user;
	_name_user = new std::string(name_user);
}


// dTor
ServerClientData::~ServerClientData()
{
	SAFE_DEL(_IP_user);
	SAFE_DEL(_name_user);
}


// set IP client
const void ServerClientData::set_IP_user(const std::string& IP)
{
	if(_IP_user != nullptr)
		delete _IP_user;

	_IP_user = new std::string(IP);
}


// get IP client
const std::string* ServerClientData::get_IP_user()
{
	return _IP_user;
}


// set port
const void ServerClientData::set_port(const unsigned short port)
{
	_port_user = port;
}


// get port
const unsigned short ServerClientData::get_port()
{
	return _port_user;
}


// set user name
const void ServerClientData::set_name_user(const std::string& userName)
{
	if(_name_user != nullptr)
		delete _name_user;

	_name_user = new std::string(userName);
}


// get user name
const std::string* ServerClientData::get_name_user()
{
	return _name_user;
}



bool ServerClientData::operator==(const sf::IpAddress &otherClient)
{
	if ((otherClient.toString() == *_IP_user))
	{
		return true;
	}
	return false;
}

bool ServerClientData::operator==(const unsigned short & otherPort)
{
	if (_port_user == otherPort)
	{
		return true;
	}
	return false;
}

