/*
 * ServerSocket.h
 *
 *  Created on: Apr 20, 2013
 *      Author: mayur
 */

#ifndef SERVERSOCKET_H_
#define SERVERSOCKET_H_

#include "Socket.h"

namespace BBot {

class ServerSocket : public Socket {
public:
	ServerSocket();
	ServerSocket(int sockfd);
	virtual ~ServerSocket();

	Socket* accept();
	static const int MAX_CONNECTIONS;

private:
	bool listen() const;
	bool connect(std::string& addr, int port) const;

	/* Object state */
private:

};

} /* namespace BBot */
#endif /* SERVERSOCKET_H_ */
