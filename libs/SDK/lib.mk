CWD			:= $(dir $(lastword $(MAKEFILE_LIST)))
SDK_DIR			 = $(CWD)/S32SDK

SDK_DEVICE		 = S32K144
SDK_DRIVERS		 = clock/S32K1xx	\
			   edma			\
			   flexcan		\
			   interrupt		\
			   osif			\
			   pins
SDK_PALS		 =
SDK_DEFINES		 = CPU_S32K144HFT0VLLT \
			   START_FROM_FLASH

SDK_INCLUDE_DIRS	 = $(SDK_DIR)/platform/devices \
			   $(SDK_DIR)/platform/devices/common \
			   $(SDK_DIR)/platform/devices/$(SDK_DEVICE)/include \
			   $(SDK_DIR)/platform/devices/$(SDK_DEVICE)/startup \
			   $(SDK_DIR)/platform/drivers/inc \
			   $(SDK_DIR)/platform/pal/inc \
			   $(SDK_DIR)/rtos/osif

SDK_SRCS		:= $(SDK_DIR)/platform/devices/startup.c \
			   $(SDK_DIR)/platform/devices/$(SDK_DEVICE)/startup/system_$(SDK_DEVICE).c \
			   $(SDK_DIR)/platform/devices/$(SDK_DEVICE)/startup/gcc/startup_$(SDK_DEVICE).S \
			   $(foreach driver,$(SDK_DRIVERS),$(wildcard $(SDK_DIR)/platform/drivers/src/$(driver)/*.c)) \
			   $(foreach pal,$(SDK_PALS),$(wildcard $(SDK_DIR)/platform/pal/src/$(pal)/*.c))

ifneq ($(filter USING_OS_FREERTOS,$(APP_DEFINES)),)
SDK_INCLUDE_DIRS	+= $(SDK_DIR)/rtos/FreeRTOS_S32K/Source/include \
			   $(SDK_DIR)/rtos/FreeRTOS_S32K/Source/portable/GCC/ARM_CM4F

SDK_SRCS		+= $(wildcard $(SDK_DIR)/rtos/FreeRTSOS_S32K/Source/*.c) \
			   $(wildcard $(SDK_DIR)/rtos/FreeRTSOS_S32K/Source/portable/GCC/ARM_CM4F/*.c) \
			   $(SDK_DIR)/rtos/osif/osif_freertos.c
else
APP_DEFINES		+= USING_OS_BAREMETAL
SDK_SRCS		+= $(SDK_DIR)/rtos/osif/osif_baremetal.c
endif

LIB_SRCS		+= $(wildcard $(CWD)/config/*.c) \
			   $(SDK_SRCS)
LIB_INCLUDE_DIRS	+= $(CWD)/config \
			   $(SDK_INCLUDE_DIRS)