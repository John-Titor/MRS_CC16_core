CWD			:= $(dir $(lastword $(MAKEFILE_LIST)))
LIB_SRCS		+= $(wildcard $(CWD)/*.c) \
			   $(wildcard $(CWD)/*.cpp)
LINKER_SCRIPT		:= $(CWD)/CC16.ld
