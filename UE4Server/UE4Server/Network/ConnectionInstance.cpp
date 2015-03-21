#include "ConnectionInstance.h"

#include <boost/bind.hpp>

#include <iostream>

ConnectionInstance::ConnectionInstance(boost::asio::ip::tcp::socket newsock) : _socket(std::move(newsock)) {
	_packet_handler = new PacketHandler();
}

void ConnectionInstance::sendAccept() {
	_read();
}

void ConnectionInstance::handleRead(const boost::system::error_code& error, size_t received) 
{
	if (!error) 
	{
		_handlePacket();
	}
	else
	{
		_handleError(error);
		return;
	}
	
	
	_read();
}

void ConnectionInstance::_handleError(const boost::system::error_code& error)
{
	if (error == boost::asio::error::eof)
	{
		std::cout << "Client disconnected. IP: " << _socket.remote_endpoint().address().to_string() << std::endl;
	}
}

void ConnectionInstance::_handlePacket()
{
	_packet_handler->HandlePacket(_buffer);
}
void ConnectionInstance::_read() {
	auto self(shared_from_this());
	_socket.async_read_some(boost::asio::buffer(_buffer, 50000),
		boost::bind(&ConnectionInstance::handleRead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}



/*void ConnectionInstance::write(std::size_t length)
{
	auto self(shared_from_this());
	PacketOK pack;
	pack.header = 1;
	boost::asio::async_write(socket, boost::asio::buffer(&pack, (size_t)sizeof(pack)),
		[this, self](boost::system::error_code ec, std::size_t)
	{
		if (!ec)
		{
			read();
		}
	});
}*/

