/*
 * Socket.cpp
 *
 *  Created on: Apr 20, 2013
 *      Author: mayur
 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cerrno>
#include <iostream>
#include <unistd.h>
#include "Comm/Socket.h"

namespace BBot {

Socket::Socket() {
	m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sockfd < 0) {
		std::cerr << "Socket create fail: " << errno << std::endl;
		m_sockfd = -1;
	}
	m_portnum = -1;
}

Socket::Socket(const int sockfd)
	:m_sockfd(sockfd) {
	m_portnum = getPortNumber();
}

Socket::~Socket() {
	if (m_sockfd >= 0)
		close(m_sockfd);
}

bool Socket::bind(int port) {
	if (m_sockfd < 0) {
		return false;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);

	if (::bind(m_sockfd, (struct sockaddr *) &addr,
				sizeof(addr)) < 0) {
		std::cerr << "Socket bind fail: " << errno << std::endl;
		return false;
	}

	m_portnum = port;
	return true;
}

int Socket::getPortNumber() const {
	if (m_sockfd < 0) {
		return -1;
	}

	if (m_portnum < 0) {
		struct sockaddr_in sin;
		socklen_t len = sizeof(sin);
		if (getsockname(m_sockfd, (struct sockaddr *)&sin, &len) < 0) {
			std::cerr << "Socket getPortNumber fail: " << errno << std::endl;
			return -1;
		} else {
			return ntohs(sin.sin_port);
		}
	}
	return m_portnum;
}

bool Socket::connect(std::string& addr, int port) const {
	if (m_sockfd < 0) {
		return false;
	}

	struct sockaddr_in server_addr = { 0 };
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	if (inet_pton(AF_INET, addr.c_str(), &server_addr.sin_addr) == 1) {
		if (::connect(m_sockfd, (struct sockaddr *)&server_addr,
				sizeof (server_addr)) < 0) {
			std::cerr << "Socket connect fail: " << errno << std::endl;
			return false;
		}
	} else {
		std::cerr << "Socket connect fail: " << EBADR << std::endl;
		return false;
	}
	return true;
}

bool Socket::send(const Command* cmds, int ncmds) const {
	if (m_sockfd < 0) {
		return false;
	}

	if(::write(m_sockfd, cmds, ncmds * sizeof (Command))<= 0) {
	  std::cerr << "Socket write fail: " << std::endl;
	  return false;
	}

	return true;
}

int Socket::receive(Command* cmds, int ncmds) const {
	if (m_sockfd < 0) {
		return -1;
	}

	ncmds = 1;
	if (::read(m_sockfd, cmds, sizeof (Command)) <= 0) {
		std::cerr << "Socket read fail: " << errno << std::endl;
		ncmds = -1;
	}
	return ncmds;
}

} /* namespace BBot */

