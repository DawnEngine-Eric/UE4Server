#include "UE4Client.h"
#include "TcpClient.h"
#include <boost/array.hpp>
#include <iostream>
#include <vector>



TcpClient::TcpClient(std::string authIp, int authPort) : resolver(ioService), socket(ioService)
{
	connect(authIp, authPort);
	instance = this;
}

TcpClient::~TcpClient() {

}

void TcpClient::connect(std::string ip, int port) {
	if (socket.is_open()) {
		socket.close();
	}

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip), port);

	boost::system::error_code error;
	socket.connect(endpoint, error);
}

void TcpClient::close()
{
	socket.close();
}

bool TcpClient::read() {
	boost::system::error_code error;
	boost::array<int, 50000> buf;

	int len = socket.read_some(boost::asio::buffer(buf), error);
	if (error == boost::asio::error::eof) {
		return false; // exit
	}

	return true;
}

bool TcpClient::send(void* data, int length) {
	char* tmpPacketData = (char *)data;

	boost::system::error_code er;
	socket.send(boost::asio::buffer(tmpPacketData, length), 0, er);

	return !er;
}

TcpClient* TcpClient::getInstance() {
	return instance;
}

TcpClient* TcpClient::instance = nullptr;