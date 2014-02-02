/*
 * GPIO.h
 *
 *  Created on: May 10, 2013
 *      Author: mayur
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <map>
#include "GPIOCommon.h"
#include "GPIOPin.h"

namespace BBot {

class GPIO {
public:
	friend class GPIOPin;
	static GPIOPin* newGPIOPin(unsigned pin_number, GPIODirection dir = GPIO_OUT) throw(gpio_exception);

private:
	GPIO();
	virtual ~GPIO() = 0;
	static void exportPin(unsigned pin_num);
	static void unexportPin(unsigned pin_num);

	/* Object state */
private:
	static int m_exportfd;
	static int m_unexportfd;
	static std::map<unsigned, GPIOPin *> m_allocedPinsMap;
};

} /* namespace BBot */
#endif /* GPIO_H_ */
