/*
 * BBotMain.cpp
 *
 *  Created on: Apr 17, 2013
 *      Author: mayur
 */


#include "BBotMain.h"
#include "Comm/ServerSocket.h"

namespace BBot {

BBotMain *BBotMain::m_instance = 0;

BBotMain::BBotMain()
	: m_mainTaskQueue("__main_queue", 0) {
	atexit(&doBotCleanup);
}

void BBotMain::doBotCleanup() {
	delete m_instance;
	m_instance = 0;
}

BBotMain::~BBotMain() {
	// TODO Auto-generated destructor stub
}

BBotMain& BBotMain::getBotInstance(int argc, char* argv[]) {
	if (m_instance == 0) {
		m_instance = new BBotMain();
	}
	return *m_instance;
}

template<class T>
void BBotMain::runOnMainTaskQueue(T t) {
	m_mainTaskQueue.enqueue(t);
}

void BBotMain::acceptDriverConnection() {
	ServerSocket serv_sock;
	Socket* datasock = 0;
	for (int port = 7000; port < 8000; port += 50) {
		std::cout << "Server attempt bind to port : " << port << std::endl;
		if (!serv_sock.bind(port))
			continue;
		datasock = serv_sock.accept();
		break;
	}

	if (m_delegate) {
		runOnMainTaskQueue([this, datasock]() {
			m_delegate->controllerDidConnect(datasock);
		});
	}

	Command *command = new Command;
	while (true) {
		int rc = datasock->receive(command, 1);
		if (rc < 0 || command->cmdType == COMMAND_STOP)
			break;

		if (m_delegate) {
			runOnMainTaskQueue([this, command]() {
				m_delegate->commandHandler(command);
			});
		}
	}
	delete command;

	delete datasock;
}

int BBotMain::runInstance(IBotDelegate* delegate) {
	/* Implements the run loop */
	m_delegate = delegate;

	BBotTask mainTask(&m_mainTaskQueue);

	if (m_delegate)
		m_delegate->initializeBot();

	BBotTaskQueue ioQueue("__io_queue");
	ioQueue.enqueue([this](){ this->acceptDriverConnection(); });

	/* Run the main processing task */
	mainTask.operator ()();

	return 0;
}

} /* namespace BBot */
