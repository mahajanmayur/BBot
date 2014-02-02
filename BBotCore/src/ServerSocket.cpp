/*
 * ServerSocket.cpp
 *
 *  Created on: Apr 20, 2013
 *      Author: mayur
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <cerrno>
#include <iostream>
#include "Comm/ServerSocket.h"

namespace BBot {

const int ServerSocket::MAX_CONNECTIONS = 5;

ServerSocket::ServerSocket()
	: Socket() {
}
ServerSocket::ServerSocket(int sockfd)
	: Socket(sockfd) {
}

ServerSocket::~ServerSocket() {
}

bool ServerSocket::listen() const {
	if (m_sockfd < 0) {
		return false;
	}

	if (::listen(m_sockfd, MAX_CONNECTIONS) < 0) {
		std::cerr << "ServerSocket listen fail: " << errno << std::endl;
		return false;
	}
	return true;
}

Socket* ServerSocket::accept () {
	if (m_sockfd < 0) {
		return 0;
	}

	listen();

	int dsock = ::accept(m_sockfd, NULL, 0);
	if (dsock < 0) {
		std::cerr << "ServerSocket accept fail: " << errno << std::endl;
		return 0;
	}
	return new Socket(dsock);
}

bool ServerSocket::connect(std::string& addr, int port) const {
	std::cerr << "ServerSocket connect fail: " << ENOSYS << std::endl;
	return false;
}

} /* namespace BBot */
