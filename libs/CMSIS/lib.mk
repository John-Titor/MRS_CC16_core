CWD			:= $(dir $(lastword $(MAKEFILE_LIST)))

REG_HEADER		:= $(OBJ_DIR)/CMSIS/S32K144.h
SVD			:= $(CWD)/S32K144.svd
SVDCPP			:= $(ROOT_DIR)/tools/svd2cpp.py

LIB_INCLUDE_DIRS	+= $(OBJ_DIR)

CMSIS_ENABLE_PERIPHS	 = FTM0 FTM1 FTM2 FTM3 \
			   PTA PTB PTC PTD PTE \
			   PORTA PORTB PORTC PORTD PORTE \
			   CAN0 CAN1 \
			   PCC WDOG \
			   ARM_FPU

CMSIS_DISABLE_PERIPHS	 = ARM_MPU
CMSIS_ALIAS_PERIPHS	 = CAN1=CAN0


GLOBAL_DEPS		+= $(REG_HEADER)
$(REG_HEADER): $(SVD) $(SVDCPP)
	@mkdir -p $(dir $@)
	$(SVDCPP) \
	--enable $(CMSIS_ENABLE_PERIPHS) \
	--disable $(CMSIS_DISABLE_PERIPHS) \
	--force-alias $(CMSIS_ALIAS_PERIPHS) \
	--defines \
	--enumerations \
	--outfile $@ \
	--emit-header $(SVD)
