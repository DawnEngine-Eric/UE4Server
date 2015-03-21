#include "ConnectionManager.h"

#include <boost/bind.hpp>


ConnectionManager::ConnectionManager(boost::asio::io_service& ioService) : acceptor(ioService, boost::asio::ip::tcp::endpoint(tcp::v4(), 25565)), socket(ioService)
{
	listenAccept();
}

ConnectionManager::~ConnectionManager() {

}

void ConnectionManager::listenAccept() {
	acceptor.async_accept(socket, boost::bind(&ConnectionManager::afterAccept, this, boost::asio::placeholders::error));
}

void ConnectionManager::afterAccept(const boost::system::error_code& error) {
	if (!error) {
		printf("New connection from %s!\n", socket.remote_endpoint().address().to_string().c_str());
		std::make_shared<ConnectionInstance>(std::move(socket))->sendAccept();
	}

	listenAccept();
}