#pragma once

class PacketHandler
{
public:

	PacketHandler();
	bool HandlePacket(char packet[5000]);
	bool HandleSwitch(unsigned char header, char data[5000]);
};