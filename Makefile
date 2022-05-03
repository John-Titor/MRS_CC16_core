#
# Top-level build script for CC16 apps
#
# Expects to be invoked with CWD = ROOT_DIR, and with a symlink SDK
# pointing to the root of the extracted S32K1xx SDK.
#
ROOT_DIR		:= $(dir $(lastword $(MAKEFILE_LIST)))
VALID_APPS		:= $(basename $(notdir $(wildcard $(ROOT_DIR)/apps/*/*.mk)))

ifneq ($(abspath $(CURDIR)),$(abspath $(ROOT_DIR)))
$(error Must invoke build from $(abspath $(ROOT_DIR)))
endif

#
# Sort out the app(s) to build.
#
APPS			?= $(VALID_APPS)
INVALID_APPS		 = $(filter-out $(VALID_APPS),$(APPS))
ifneq ($(INVALID_APPS),)
$(error Invalid application(s): $(INVALID_APPS))
endif

ACTIONS			 = build clean
APP_ACTIONS		 = $(foreach action,$(ACTIONS),$(foreach app,$(APPS),$(action)~$(app)))

.PHONY: build
build:	$(filter build~%,$(APP_ACTIONS))

.PHONY: clean
clean:	$(filter clean~%,$(APP_ACTIONS))

$(APP_ACTIONS):	action = $(word 1,$(subst ~, ,$@))
$(APP_ACTIONS):	app = $(word 2,$(subst ~, ,$@))
$(APP_ACTIONS):
	@echo $(action): $(app)
	$(if $(VERBOSE),,@)$(MAKE) -f $(ROOT_DIR)/rules.mk \
		ROOT_DIR=$(ROOT_DIR) \
		OBJ_DIR=$(ROOT_DIR)/obj \
		APP_NAME=$(app) \
		VERBOSE=$(VERBOSE) \
		$(action)
