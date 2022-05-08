#
# Build a CC16 app.
#
# Call with:
#
# ROOT_DIR
#	Root directory of the project.
#
# APP_NAME
#	Name of the app directory, containg $(APP_NAME).mk and (typically) app sources.
#
# OBJ_DIR
#	Where objects and the output files will be placed.
#
ifeq ($(ROOT_DIR),)
$(error Must set ROOT_DIR)
endif
ifeq ($(OBJ_DIR),)
$(error Must set OBJ_DIR)
endif
ifeq ($(APP_NAME),)
$(error Must set APP_NAME)
endif

APP_DIR			:= $(ROOT_DIR)/apps/$(APP_NAME)
APP_MK_INCLUDE		:= $(APP_DIR)/$(APP_NAME).mk
include $(APP_MK_INCLUDE)
APP_SRC_DIRS		?= $(APP_DIR)
APP_INCLUDE_DIRS	?= $(APP_DIR)
APP_SRCS		?= $(foreach src_dir,$(APP_SRC_DIRS),$(wildcard $(src_dir)/*.c) \
			   				     $(wildcard $(src_dir)/*.cpp) \
			   				     $(wildcard $(src_dir)/*.S))

GLOBAL_DEPS		:=
LIB_DEFINES		:=
LIB_SRCS		:=
LIB_INCLUDE_DIRS	:= $(ROOT_DIR)/libs
LIBS			:= $(APP_LIBS) CC16 CMSIS ETL
LIB_DIRS		:= $(foreach lib,$(LIBS),$(ROOT_DIR)/libs/$(lib))
LIB_MK_INCLUDES		:= $(foreach lib_dir,$(LIB_DIRS),$(lib_dir)/lib.mk)
include $(LIB_MK_INCLUDES)

TOOL_PREFIX		 = arm-none-eabi
CC			:= $(TOOL_PREFIX)-gcc
CXX			:= $(TOOL_PREFIX)-g++
LD			:= $(CC)
OBJCOPY			:= $(TOOL_PREFIX)-objcopy
SIZE			:= $(TOOL_PREFIX)-size

ARCH_FLAGS		 = -march=armv7e-m+fp \
			   -mthumb \
			   -mfloat-abi=hard \
			   -mfpu=fpv4-sp-d16

INCLUDES		:= $(addprefix -I,$(APP_INCLUDE_DIRS) $(LIB_INCLUDE_DIRS))

ASFLAGS			:= $(ARCH_FLAGS) \
			   $(addprefix -D,$(APP_DEFINES) $(LIB_DEFINES)) \
			   $(INCLUDES) \
			   $(APP_ASFLAGS)

COMMON_FLAGS		:= $(ARCH_FLAGS) \
			   $(addprefix -D,$(APP_DEFINES) $(LIB_DEFINES)) \
			   $(INCLUDES) \
			   -ffreestanding \
			   -Os \
			   -ffunction-sections \
			   -fdata-sections \
			   -funsigned-char \
			   -funsigned-bitfields \
			   -fshort-enums \
			   -fno-jump-tables \
			   -Wall \
			   -Wdouble-promotion \
			   -ffast-math \
			   -fsingle-precision-constant \
			   -flto \
			   -MMD

CFLAGS			:= $(COMMON_FLAGS) \
			   -std=gnu2x \
			   $(APP_CFLAGS)

CXXFLAGS		:= $(COMMON_FLAGS) \
			   -std=gnu++17 \
			   -fno-exceptions \
			   -fno-rtti \
			   -fno-use-cxa-atexit \
			   $(APP_CXXFLAGS)

LDFLAGS			:= $(COMMON_FLAGS) \
			   -nostartfiles \
			   -nodefaultlibs \
			   -nostdlib \
			   --entry=Reset_Handler \
			   -Wl,-gc-sections \
			   -Wl,-T,$(LINKER_SCRIPT) \
			   -lgcc \
			   -lm \
			   -lc \
			   --specs=nosys.specs \
			   $(APP_LDFLAGS)

BUILD_DIR		:= $(OBJ_DIR)/$(APP_NAME)
APP_ELF			:= $(BUILD_DIR)/$(APP_NAME).elf
APP_SREC		:= $(BUILD_DIR)/$(APP_NAME).s19

SRCS			:= $(APP_SRCS) $(LIB_SRCS)
SOBJS			:= $(patsubst %.S,%.o,$(filter %.S,$(SRCS)))
COBJS			:= $(patsubst %.c,%.o,$(filter %.c,$(SRCS)))
CPPOBJS			:= $(patsubst %.cpp,%.o,$(filter %.cpp,$(SRCS)))

OBJS			:= $(addprefix $(BUILD_DIR)/, $(SOBJS) $(COBJS) $(CPPOBJS))
DEPS			:= $(OBJS:.o=.d)

GLOBAL_DEPS		+= $(MAKEFILE_LIST) $(LINKER_SCRIPT)

.PHONY: build
build: $(APP_SREC)

$(APP_SREC): $(APP_ELF) $(GLOBAL_DEPS)
	@echo @@ $(APP_NAME) @@ Srec $(notdir $@)
	@mkdir -p $(@D)
	@$(SIZE) $<
	$(if $(VERBOSE),,@)$(OBJCOPY) \
		--output-target srec \
		--srec-forceS3 \
		$< $@

$(APP_ELF): $(OBJS) $(GLOBAL_DEPS)
	@echo @@ $(APP_NAME) @@ Link $(notdir $@)
	@mkdir -p $(@D)
	$(if $(VERBOSE),,@)$(LD) -o $@ $(OBJS) $(LDFLAGS) \
	   -Wl,-Map=$(@:.elf=.map)

$(BUILD_DIR)/%.o: %.S $(GLOBAL_DEPS)
	@echo @@ $(APP_NAME) @@ Compile $(notdir $@)
	@mkdir -p $(@D)
	$(if $(VERBOSE),,@)$(CC) -c $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.c $(GLOBAL_DEPS)
	@echo @@ $(APP_NAME) @@ Compile $(notdir $@)
	@mkdir -p $(@D)
	$(if $(VERBOSE),,@)$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.cpp $(GLOBAL_DEPS)
	@echo @@ $(APP_NAME) @@ Compile $(notdir $@)
	@mkdir -p $(@D)
	$(if $(VERBOSE),,@)$(CXX) -c $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	@echo @@ $(APP_NAME) @@ Clean
	$(if $(VERBOSE),,@)rm -rf $(BUILD_DIR)

-include $(DEPS)
