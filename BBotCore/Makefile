################################################################################
#
# Makefile for BBotCore shared library
#	Author: Mayur Mahajan
#
################################################################################

MAJOR = 1
MINOR = 0
TARGET_NAME := BBotCore
PROJECT_TYPE := lib

-include ../tools.mk

SRCS := $(wildcard src/*.cpp)
OBJS := $(addprefix obj/,$(notdir $(SRCS:.cpp=.o)))

LIBS += -lpthread
INCLUDE_DIR += -I./include

-include ../make.mk
