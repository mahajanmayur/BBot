/*
 * BBotTaskQueue.cpp
 *
 *  Created on: Jan 12, 2014
 *      Author: mayur
 */

#include "Common/BBotTaskQueue.h"

#include <iostream>

namespace BBot {

void BBotTask::operator ()() {
	while (true) {
		std::function <void()> task;
		{
			std::unique_lock <std::mutex> lock(m_owner->m_qmutex);

			while (m_owner->m_tasks.empty()) {
				if (!m_owner->m_stop)
					m_owner->m_condition.wait(lock);
				else return;
			}

			task = m_owner->m_tasks.front();
			m_owner->m_tasks.pop_front();
		}
		task();
	}
}

BBotTaskQueue::BBotTaskQueue(const std::string &name, size_t size)
	: m_name(name), m_stop(false) {
	for (size_t i = 0; i < size; ++i) {
		m_workers.push_back(std::thread(BBotTask(this)));
	}
}

BBotTaskQueue::~BBotTaskQueue() {
	m_stop = true;
	m_condition.notify_all();

	for (size_t i = 0; i < m_workers.size(); ++i) {
		m_workers[i].join();
	}
}

} /* namespace BBot */
