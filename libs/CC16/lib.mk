CWD			:= $(dir $(lastword $(MAKEFILE_LIST)))
LIB_SRCS		+= $(wildcard $(CWD)/*.c)
LIB_INCLUDE_DIRS	+= $(CWD)
