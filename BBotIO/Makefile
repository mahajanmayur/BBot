################################################################################
#
# Makefile for BBotIO shared library
#	Author: Mayur Mahajan
#
################################################################################

MAJOR = 1
MINOR = 0
TARGET_NAME := BBotIO
PROJECT_TYPE := lib

-include ../tools.mk

SRCS := $(wildcard src/*.cpp)
OBJS := $(addprefix obj/,$(notdir $(SRCS:.cpp=.o)))

INCLUDE_DIR += -I./include

-include ../make.mk
