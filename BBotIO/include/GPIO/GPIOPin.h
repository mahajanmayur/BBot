/*
 * GPIOPin.h
 *
 *  Created on: May 10, 2013
 *      Author: mayur
 */

#ifndef GPIOPIN_H_
#define GPIOPIN_H_

#include "GPIOCommon.h"

namespace BBot {

class GPIOPin {
public:
	friend class GPIO;
	~GPIOPin();
	int getValue() const throw(gpio_exception);
	void setValue(int value) throw(gpio_exception);
	void setDirection(GPIODirection dir) throw(gpio_exception);
	GPIODirection getDirection() const;


private:
	GPIOPin(unsigned int pin_number, GPIODirection dir, void (*cleanup)(unsigned)) throw(gpio_exception);

	/* Object state */
private:
	unsigned m_pinNumber;
	GPIODirection m_direction;
	int m_valueFile;
	void (*m_cleanup_cb)(unsigned);
};

} /* namespace BBot */
#endif /* GPIOPIN_H_ */
