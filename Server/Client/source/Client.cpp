#include "Client.h"
#include <thread>
#include <string>
#include <iostream>

// cTor
Client::Client() : _port_server(50000), _counter(0)
{
	_socket_user = new sf::UdpSocket();
	_socket_user->bind(sf::Socket::AnyPort);
	_port_user = _socket_user->getLocalPort();

	_IP_user = new std::string(sf::IpAddress::getLocalAddress().toString());
	_IP_server = new std::string("127.0.0.1");
	_name_user = new std::string("...");
	_pass_user = new std::string("...");
}


// dTor
Client::~Client()
{
	SAFE_DEL(_socket_user);
	SAFE_DEL(_IP_user);
	SAFE_DEL(_IP_server);
	SAFE_DEL(_name_user);
	SAFE_DEL(_pass_user);
}

const void Client::send_message()
{
	
	std::string message;

	std::cout << "Please pick a display name: ";
	std::getline(std::cin, message);	//get a display name
	std::string name = message;
	set_name_user(name);
	_socket_user->send(message.c_str(), message.size() + 1, *_IP_server, _port_server);

	while (true)
	{
		std::cout << name << ": ";
		std::getline(std::cin, message);

		std::string new_message = *message_function(message);

		_socket_user->send(new_message.c_str(), new_message.size() + 1, *_IP_server, _port_server);
	}
}

const void Client::recieve_message()
{
	if (_counter < 1)
	{
		while (true)
		{
			char buffer[1024];
			std::size_t received = 0;
			sf::IpAddress sender;
			unsigned short port;

			_socket_user->receive(buffer, sizeof(buffer), received, sender, port);
			_port_server = 50001;

			_counter++;

			break;
		}
	}


	while (true)
	{
		char buffer[1024];
		std::size_t received = 0;
		sf::IpAddress sender;
		unsigned short port;
		_socket_user->receive(buffer, sizeof(buffer), received, sender, port);
		std::cout << buffer << std::endl;
	}
}


// messsage function
const std::string * Client::message_function(const std::string& message)
{
	std::string* message_pack = new std::string("^");
	std::string tmp;
	int index_pos = 0;

	message_pack->append(*_name_user);
	message_pack->append("^");
	

	// get message type
	if (message[0] == '@')
	{

		for (size_t i = 0; i < message.size(); i++)
		{
			tmp += message[i];

			if (message[i + 1] == ' ')
			{
				tmp.append("^");
				message_pack->append(tmp);

				i++;
				index_pos = i;
				break;
			}
		}
	}
	else
	{
		message_pack->append("^");
	}

	
	
	tmp.clear();

	// get actual message
	for (size_t j = index_pos; j < message.size(); j++)
	{
		tmp += message[j];
	}
	message_pack->append(tmp);
	
	return message_pack;
}


// set IP client
const void Client::set_IP_user(const std::string& IP)
{
	if(_IP_user != nullptr)
		delete _IP_user;

	_IP_user = new std::string(IP);
}


// get IP client
const std::string* Client::get_IP_user()
{
	return _IP_user;
}


// set IP server
const void Client::set_IP_server(const std::string& IP)
{
	if(_IP_server != nullptr)
		delete _IP_server;

	_IP_server = new std::string(IP);
}


// get IP server
const std::string* Client::get_IP_server()
{
	return _IP_server;
}


// set port
const void Client::set_port(const unsigned short port)
{
	_port_user = port;
}


// get port
const unsigned short Client::get_port()
{
	return _port_user;
}


// set user name
const void Client::set_name_user(const std::string& userName)
{
	if(_name_user != nullptr)
		delete _name_user;

	_name_user = new std::string(userName);
}


// get user name
const std::string* Client::get_name_user()
{
	return _name_user;
}


// set pass user
const void Client::set_pass_user(const std::string& userPass)
{
	if(_pass_user != nullptr)
		delete _pass_user;

	_pass_user = new std::string(userPass);
}


// get pass user
const std::string* Client::get_pass_user()
{
	return _pass_user;
}


// orbit
const void Client::orbit()
{
	
	/*std::cout << "Connect to server IP: ";
	std::cin >> tmpIP;
	set_IP_server(tmpIP);

	std::cout << "Connect to server port: ";
	std::cin >> _port_server;*/

	while (true)
	{
		std::thread sendThread(&Client::send_message, this);
		std::thread recieveThread(&Client::recieve_message, this);

		sendThread.join();
		recieveThread.join();
	}
	
	//std::cout << *message_function("@hej2 jag vill vara en häst");
}
