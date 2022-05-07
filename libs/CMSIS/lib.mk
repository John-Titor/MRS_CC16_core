CWD			:= $(dir $(lastword $(MAKEFILE_LIST)))

REG_HEADER		:= $(OBJ_DIR)/CMSIS/S32K144.h
SVD			:= $(CWD)/S32K144.svd
SVDCPP			:= $(ROOT_DIR)/tools/svd2cpp.py

LIB_INCLUDE_DIRS	+= $(OBJ_DIR)

CMSIS_DISABLE_PERIPHS	 = ARM_MPU	# actually NXP MPU
CMSIS_ALIAS_PERIPHS	 = CAN1=CAN0	# CAN1/2 are proper subsets

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
