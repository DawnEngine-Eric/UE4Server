#include "PacketHandler.h"
#include "../Utils/var_helper.h"
#include "../Config/packet.h"
#include "../Config/config.h"
#include <iostream>

PacketHandler::PacketHandler()
{

}

bool PacketHandler::HandlePacket(char packet[5000])
{
	BYTE header;
	header = packet[0];

	std::cout << "Packet received! Header: " << (int)header << std::endl;
	
	return HandleSwitch(header, packet);
}

bool PacketHandler::HandleSwitch(BYTE header, char data[5000])
{
	if (header >= HEADER_GC_MAX)
	{
		return false;
	}

	switch (header)
	{
	case HEADER_GC_VERSION:
		CGVersion s_data;
		memcpy(&s_data, data, sizeof(data));
		char actual_version[VERSION_MAX_LENGTH];
		sprintf(actual_version, "v%u.%u", MAJOR_VERSION, MINOR_VERSION);
		if (std::string(actual_version) == std::string(s_data.version))
		{
			std::cout << "Client version: " << s_data.version << " (valid)" << std::endl;
		}
		else
		{
			std::cout << "Client version: " << s_data.version << " (invalid)" << std::endl;
		}
		break;
	}
}