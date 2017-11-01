#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <map>

using std::string;

int main()
{
	// Create a socket and bind it to the port 55002
	sf::UdpSocket socket;
	socket.bind(55002);


	// Message Variables
	char buffer[1024];
	std::size_t received = 0;
	sf::IpAddress sender;
	unsigned short port;
	std::map<INT32, std::string> chatters;

	socket.receive(buffer, sizeof(buffer), received, sender, port);

	for (int i = 0; i < 10; i++)
	{
	
		string message;
		INT32 senderInt = sender.toInteger();
			if (chatters.find(senderInt) == chatters.end())
			{
				string tempStr(buffer);
				int maxLength = 10;

				if (tempStr.size() < maxLength)
				{
						maxLength = tempStr.size();
				}//ensures names is not longer than 10 characters

				string newName = tempStr.substr(0, maxLength);
				chatters[senderInt] = newName;
				std::cout << newName << " has connected " << std::endl;

			}
			else
			{
				
				socket.receive(buffer, sizeof(buffer), received, sender, port);
				message = chatters[senderInt] + " : " + buffer;
				std::cout << message << std::endl;
			}

	//	socket.send(message.c_str(), message.size() + 1, sender, port+1);

	}

	/*for (auto it = chatters.cbegin(); it != chatters.cend(); ++it)
	{
		std::cout << it->first << " " << it->second + "\n";
	}*/
	
	return 0;
}