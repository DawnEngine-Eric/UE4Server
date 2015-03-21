#pragma once

#include <string>
#include "AllowWindowsPlatformTypes.h"
#include <boost/asio.hpp>
#include "HideWindowsPlatformTypes.h"

class TcpClient
{
	public:
		TcpClient(std::string authIp, int authPort);
		~TcpClient();

		void connect(std::string ip, int port);
		void close();
		bool read();
		bool send(void* data, int length);

		static TcpClient* getInstance();

	private:
		boost::asio::io_service ioService;
		boost::asio::ip::tcp::resolver resolver;
		boost::asio::ip::tcp::socket socket;

		static TcpClient* instance;
};