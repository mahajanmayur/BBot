/*
 * Socket.h
 *
 *  Created on: Apr 20, 2013
 *      Author: mayur
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>
#include "../Common/Command.h"

namespace BBot {

class Socket {
public:
	Socket();
	Socket(const int sockfd);
	virtual ~Socket();

	bool bind(int port);
	virtual bool connect(std::string& addr, int port) const;
	int getPortNumber() const;

	bool send(const Command *cmds, int ncmds) const;
	int receive(Command *cmds, int ncmds) const;

	/* Object state */
protected:
	int m_sockfd;
	int m_portnum;
};

} /* namespace BBot */
#endif /* SOCKET_H_ */
