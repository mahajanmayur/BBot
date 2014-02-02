/*
 * BBotTaskQueue.h
 *
 *  Created on: Jan 12, 2014
 *      Author: mayur
 */

#ifndef BBOTTASKQUEUE_H_
#define BBOTTASKQUEUE_H_

#include <vector>
#include <deque>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

namespace BBot {

class BBotTaskQueue;

class BBotTask {
public:
	BBotTask(BBotTaskQueue *q) : m_owner(q) { }
	void operator()();

private:
	BBotTaskQueue *m_owner;
};

class BBotTaskQueue {
public:
	BBotTaskQueue(const std::string &name, size_t size = 1);
	virtual ~BBotTaskQueue();

	template<class T> void enqueue(T t) {
		{
			std::unique_lock <std::mutex> lock(m_qmutex);
			m_tasks.push_back(std::function<void()>(t));
		}
		m_condition.notify_one();
	}

private:
	friend class BBotTask;

	std::string m_name;
	std::vector <std::thread> m_workers;
	std::deque <std::function <void()>> m_tasks;

	std::mutex m_qmutex;
	std::condition_variable m_condition;
	bool m_stop;
};

} /* namespace BBot */
#endif /* BBOTTASKQUEUE_H_ */
