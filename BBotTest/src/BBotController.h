/*
 * BBotController.h
 *
 *  Created on: May 12, 2013
 *      Author: mayur
 */

#ifndef BBOTCONTROLLER_H_
#define BBOTCONTROLLER_H_

#include "BBotHeader.h"

namespace BBot {

class BBotController : public IBotDelegate {
public:
	BBotController();
	virtual ~BBotController();

	/* IBotDelegate notifications */
	void initializeBot();
	void controllerDidConnect(Socket *socket);
	bool commandHandler(Command *command);
};

} /* namespace BBot */
#endif /* BBOTCONTROLLER_H_ */
