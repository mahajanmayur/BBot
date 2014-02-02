/*
 * GPIO.cpp
 *
 *  Created on: May 10, 2013
 *      Author: Mayur Mahajan
 */

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include "GPIO/GPIO.h"

namespace BBot {

#define MAX_BUF_LEN 16

  int GPIO::m_exportfd = open(GPIO_SYSFS_DIR"/export", O_WRONLY);
  int GPIO::m_unexportfd = open(GPIO_SYSFS_DIR"/unexport", O_WRONLY);
  std::map<unsigned, GPIOPin *> GPIO::m_allocedPinsMap;

  GPIOPin* GPIO::newGPIOPin(unsigned int pin_number, GPIODirection dir) throw(gpio_exception) {
    GPIOPin *pin =  NULL;
    if ((m_exportfd < 0) || (m_unexportfd < 0)) {
      throw_gpio_exception(pin_number, dir, -1);
    }

    exportPin(pin_number);
    try {
      pin = new GPIOPin(pin_number, dir, unexportPin);
    } catch (const std::exception &e) {
      unexportPin(pin_number);
      throw;
    }
    m_allocedPinsMap[pin_number] = pin;
    return pin;
  }

  GPIO::GPIO() {
  }

  void GPIO::exportPin(unsigned int pin_num) {
    int len;
    char buf[MAX_BUF_LEN];
    len = snprintf(buf, sizeof (buf), "%d", pin_num);
    if (write(m_exportfd, buf, len) <= 0) {
      std::cerr << "Failed to export GPIO Pin " << pin_num << std::endl;
    }
  }

  void GPIO::unexportPin(unsigned int pin_num) {
    int len;
    char buf[MAX_BUF_LEN];
    len = snprintf(buf, sizeof (buf), "%d", pin_num);
    if (write(m_unexportfd, buf, len) <= 0) {
      std::cerr << "Failed to unexport GPIO Pin " << pin_num << std::endl;
    } else {
      m_allocedPinsMap[pin_num] = NULL;
    }
  }

} /* namespace BBot */

