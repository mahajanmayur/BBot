/*
 * main.cpp
 *
 *  Created on: Apr 17, 2013
 *      Author: mayur
 */

#include "BBotMain.h"
#include "BBotController.h"

using namespace BBot;

int main(int argc, char *argv[])
{
	return (BBotMain::getBotInstance(argc, argv).runInstance(new BBotController()));
}


