################################################################################
#
# Makefile for BBot Framework Test Application
#	Author: Mayur Mahajan
#
################################################################################

TARGET_NAME := BBotTest
PROJECT_TYPE := exec

-include ../tools.mk

LIBS_DIR += -L../BBotCore -L../BBotIO
LIBS += -lBBotCore -lBBotIO -lpthread
INCLUDE_DIR += -I../BBotCore/include -I../BBotIO/include

SRCS := $(wildcard src/*.cpp)
OBJS := $(addprefix obj/,$(notdir $(SRCS:.cpp=.o)))

-include ../make.mk
