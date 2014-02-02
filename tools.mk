################################################################################
#
# Makefile environment for BBot
#	Author: Mayur Mahajan
#
################################################################################
ROOT_DIR := $(shell pwd)/..

#Set for Debug mode or non-debug
BUILD := devel # devel OR rel

#Set Architecture
ARCH := arm

#Compilers
ifeq ($(ARCH),arm)
CC := arm-linux-gnueabihf-g++
GCC := arm-linux-gnueabihf-gcc
else
CC := g++
GCC := gcc
endif

#Miscellaneous helpers
RM := rm -rf
ECHO := echo

#Toolchain includes
INCLUDE_DIR = -I/usr/arm-linux-gnueabihf/include/ -I/usr/arm-linux-gnueabihf/include/c++ \
		-I$(ROOT_DIR)/Depends/include
LIBS_DIR = -L/usr/arm-linux-gnueabihf/lib -L$(ROOT_DIR)/Depends/lib

#BuildTool flags
ifeq ($(BUILD),devel)
AS_FLAGS = -g
CPP_COMPILE_FLAGS = -g -O0 -fno-omit-frame-pointer -pipe -DDEBUG
CPP_LINK_FLAGS = -g
C_COMPILE_FLAGS = -g -O0 -fno-omit-frame-pointer -pipe -DDEBUG
C_LINK_FLAGS = -g
else
AS_FLAGS =
CPP_COMPILE_FLAGS = -O3 -Werror
CPP_LINK_FLAGS =
C_COMPILE_FLAGS = -O2 -fomit-frame-pointer -D__USE_STRING_INLINES -pipe
C_LINK_FLAGS =
endif

#Common BuildTool flags
CPP_COMPILE_FLAGS += -Wall -std=c++11
C_COMPILE_FLAGS += -Wall

#Set the file extension and prefix if lib
ifeq ($(PROJECT_TYPE),lib)
TARGET_PREFIX = lib
TARGET_POSTFIX = .so
CPP_COMPILE_FLAGS += -fPIC
CPP_LINK_FLAGS += -shared
TARGET = $(TARGET_PREFIX)$(TARGET_NAME)$(TARGET_POSTFIX).$(MAJOR).$(MINOR)
else
TARGET = $(TARGET_PREFIX)$(TARGET_NAME)$(TARGET_POSTFIX)
endif

#Global Build Macros
DEFINES +=
