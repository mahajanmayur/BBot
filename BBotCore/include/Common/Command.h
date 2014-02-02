/*
 * Command.h
 *
 *  Created on: Apr 21, 2013
 *      Author: mayur
 */

#ifndef COMMAND_H_
#define COMMAND_H_

typedef enum {
	COMMAND_NULL,
	COMMAND_STOP,
	COMMAND_SENSE,
	COMMAND_ACTIVATE,
	COMMAND_DRIVE,
	COMMAND_MAX
} CommandType;

#define CMD_BUF_SZ 64

typedef struct {
	CommandType	cmdType;
	size_t		cmdSize;
	char		cmdBuf[CMD_BUF_SZ];
} Command;


#endif /* COMMAND_H_ */
