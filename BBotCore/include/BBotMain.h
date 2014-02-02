/*
 * BBotMain.h
 *
 *  Created on: Apr 17, 2013
 *      Author: Mayur Mahajan
 */

#ifndef BBOTMAIN_H_
#define BBOTMAIN_H_

#include "BBotHeader.h"
#include "Common/BBotTaskQueue.h"

namespace BBot {

class BBotMain {
public:
	static BBotMain	&getBotInstance(int argc, char *argv[]);
	int				runInstance(IBotDelegate* delegate);
	template<class T> void runOnMainTaskQueue(T t);

private:
	BBotMain();
	~BBotMain();
	static void		doBotCleanup();
	void 			acceptDriverConnection();

	/* Object state */
private:
	static BBotMain	*m_instance;
	IBotDelegate*	m_delegate;
	BBotTaskQueue	m_mainTaskQueue;
};

} /* namespace BBot */
#endif /* BBOTMAIN_H_ */
