#include "Network/ConnectionManager.h"

#include <iostream>

int main() {
	//PacketManager::getInstance()->registerPacket(84, testPacket);
	std::cout << "Starting UE4Server...\n";
	boost::asio::io_service ioService;
	ConnectionManager server(ioService);
	ioService.run();
	return 0;
}