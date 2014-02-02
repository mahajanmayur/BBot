/*
 * BBotController.cpp
 *
 *  Created on: May 12, 2013
 *      Author: mayur
 */

#include "BBotController.h"
#include "GPIO/GPIO.h"

namespace BBot {

BBotController::BBotController() {
	// TODO Auto-generated constructor stub
	std::shared_ptr<int> aptr(new int);
}

BBotController::~BBotController() {
	// TODO Auto-generated destructor stub
}

void BBotController::initializeBot() {
	std::cout << "BBot initialization done." << std::endl;
}

void BBotController::controllerDidConnect(Socket *socket)
{
	std::cout << "Controller connected!!" << std::endl;

	try {
		GPIOPin *pin = GPIO::newGPIOPin(60, GPIO_OUT);
		for (unsigned int i = 1; i < 5; ++i) {
			std::cout << "set value " << (i & 1) << std::endl;
			pin->setValue(i & 1);
			sleep(1);
		}
		delete pin;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

bool BBotController::commandHandler(Command *command) {
	std::cout << "command handler received command " << command->cmdType << std::endl;
	return true;
}

} /* namespace BBot */
