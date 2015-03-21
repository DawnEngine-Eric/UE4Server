#ifndef __CONNECTION_INSTANCE_H__
#define __CONNECTION_INSTANCE_H__

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "PacketHandler.h"
class ConnectionInstance : public std::enable_shared_from_this<ConnectionInstance>
{
public:

	ConnectionInstance(boost::asio::ip::tcp::socket newsock);

	void sendAccept();
	void handleWrite(const boost::system::error_code& error, size_t transferred);
	void handleRead(const boost::system::error_code& error, size_t received);
private:
	boost::asio::ip::tcp::socket _socket;

	char _buffer[5000];
	PacketHandler * _packet_handler;

	void _read();
	//void write(std::size_t length);

	void _handleError(const boost::system::error_code& error);
	void _handlePacket();
};
#endif