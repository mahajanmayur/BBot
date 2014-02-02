/*
 * IBotDelegate.h
 *
 *  Created on: Apr 17, 2013
 *      Author: mayur
 */

#ifndef IBOTDELEGATE_H_
#define IBOTDELEGATE_H_

#include "Common/Command.h"

namespace BBot {

class Socket;

class IBotDelegate {
public:
	IBotDelegate() {}
	virtual ~IBotDelegate() {}

	virtual void initializeBot() = 0;
	virtual void controllerDidConnect(Socket *socket) = 0;
	virtual bool commandHandler(Command *command) = 0;
};

} /* namespace BBot */
#endif /* IBOTDELEGATE_H_ */
