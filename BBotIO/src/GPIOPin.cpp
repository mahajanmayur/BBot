/*
 * GPIOPin.cpp
 *
 *  Created on: May 10, 2013
 *      Author: Mayur Mahajan
 */

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include "GPIO/GPIOPin.h"

namespace BBot {

#define MAX_BUF_LEN 256

  GPIOPin::~GPIOPin() {
    m_cleanup_cb (m_pinNumber);
    close (m_valueFile);
  }

  void GPIOPin::setDirection(GPIODirection dir) throw (gpio_exception) {
    if (dir != GPIO_IN && dir != GPIO_OUT)
      throw_gpio_exception(m_pinNumber, dir, -1);

    if (m_direction != dir) {
      char buf[MAX_BUF_LEN];
      sprintf(buf, GPIO_SYSFS_DIR"/gpio%d/direction", m_pinNumber);

      int dir_fd = open(buf, O_WRONLY);
      if (dir_fd < 0) {
	throw_gpio_exception(m_pinNumber, dir, -1);
      }

      std::string strdirection = gpioDirectionStr(dir);
      if (::write(dir_fd, strdirection.c_str(), strdirection.length()) <= 0) {
	std::cerr << "Failed to set GPIO direction" << std::endl;
      } else {
	m_direction = dir;
      }
    }
  }

  GPIODirection GPIOPin::getDirection() const {
    return m_direction;
  }

  int GPIOPin::getValue() const throw(gpio_exception) {
    char buf[MAX_BUF_LEN];
    int len = read(m_valueFile, buf, sizeof (buf));
    if (len < 0)
      throw_gpio_exception(m_pinNumber, m_direction, -1);

    buf[len] = '\0';
    return atoi(buf);
  }

  void GPIOPin::setValue(int value) throw(gpio_exception) {
    char buf[MAX_BUF_LEN];
    int len = snprintf(buf, sizeof (buf), "%d", value);
    len = write(m_valueFile, buf, len);
    if (len < 0)
      throw_gpio_exception(m_pinNumber, m_direction, value);
  }

  GPIOPin::GPIOPin(unsigned int pin_number, GPIODirection dir, void (*cleanup)(unsigned)) throw(gpio_exception):
    m_pinNumber(pin_number), m_cleanup_cb(cleanup) {
    char buf[MAX_BUF_LEN];
    sprintf(buf, GPIO_SYSFS_DIR"/gpio%d/value", pin_number);

    setDirection(dir);
    m_valueFile = open(buf, O_RDWR);
    if (m_valueFile < 0)
      throw_gpio_exception(m_pinNumber, dir, -1);
  }

} /* namespace BBot */
