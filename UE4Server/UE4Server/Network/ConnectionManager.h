#ifndef __CONNECTION_MANAGER_H__
#define __CONNECTION_MANAGER_H__
#include <boost/asio.hpp>

#include "ConnectionInstance.h"

using boost::asio::ip::tcp;
class ConnectionManager 
{
	public:
		ConnectionManager(boost::asio::io_service& ioService);
		~ConnectionManager();
		
		tcp::socket socket;
	private:
		boost::asio::ip::tcp::acceptor acceptor;
		boost::asio::io_service _ioService;
		void listenAccept();
		void afterAccept(const boost::system::error_code& error);

		
};
#endif