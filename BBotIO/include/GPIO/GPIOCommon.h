/*
 * GPIOCommon.h
 *
 *  Created on: May 10, 2013
 *      Author: mayur
 */

#ifndef GPIOCOMMON_H_
#define GPIOCOMMON_H_

#include <stdexcept>
#include <sstream>
#include <string>

#define GPIO_SYSFS_DIR "/sys/class/gpio"

namespace BBot {

typedef enum {
	GPIO_IN = 0,
	GPIO_OUT = 1,
} GPIODirection;

static std::string gpioDirectionStr(GPIODirection dir) {
	std::string str_direction = "UNK";

	if (dir == GPIO_IN)
		str_direction = "in";
	else if (dir == GPIO_OUT)
		str_direction = "out";

	return str_direction;
}

class gpio_exception : public std::runtime_error {
public:
	explicit gpio_exception(unsigned pnum, GPIODirection dir,
			unsigned value, const char *file, int line) :
			std::runtime_error("gpio exception> "),
			_pnum(pnum), _value(value), _dir(dir),
			_file(file), _line(line) { }

	virtual ~gpio_exception() throw () {}

	virtual const char* what() const throw () {
		std::ostringstream strss;

		strss << "[" << _file << ":" << _line << "] ";
		strss << "pin:" << _pnum << " direction:" << gpioDirectionStr(_dir);
		strss << " value:" << std::hex << _value;

		std::string error_msg = std::runtime_error::what();
		error_msg += strss.str();

		return error_msg.c_str();
	}

private:
	unsigned _pnum, _value;
	GPIODirection _dir;
	std::string _file;
	int _line;
};

#define throw_gpio_exception(_x_pin, _x_dir, _x_val) throw gpio_exception(_x_pin, _x_dir, _x_val, __FILE__, __LINE__)

} /* namespace BBot */
#endif /* GPIOCOMMON_H_ */
