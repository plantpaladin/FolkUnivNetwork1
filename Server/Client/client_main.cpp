#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <future>
#include <thread>

using std::string;
void receive(unsigned short portNr)
{
	sf::UdpSocket socket;
	socket.bind(portNr);
	while (true)
	{
		char buffer[1024];
		std::size_t received = 0;
		sf::IpAddress sender;
		unsigned short port;
		socket.receive(buffer, sizeof(buffer), received, sender, port);
		std::cout << buffer << std::endl;
		
	}
}

int main()
{
	sf::UdpSocket socket;
	unsigned short portNumber = 5502;
	socket.bind(portNumber);
	std::thread receiveThread = std::thread(receive, portNumber + 1);//uses the +1 number for recieve
	string message;

	std::cout << "Please pick a display name: \n";
	getline(std::cin, message);	//get a display name
	string name = message;
	socket.send(message.c_str(), message.size() + 1, "127.0.0.1", 55002);


	while (true)
	{
		getline(std::cin, message);	//"Mattis";//+ sf::IpAddress::getLocalAddress().toString();
		std::cout << name << ": " << message;


		socket.send(message.c_str(), message.size() + 1, "127.0.0.1", 55002);
		
	}
	
	
		
	
	receiveThread.join();
	return 0;
}