#
# App configuration makefile.
#
# Called with:
#
# APP_DIR
#	Path to the directory containing this Makefile.
#
# APP_NAME
#	Name of the app being built.
#
# May override:
#
# APP_SRC_DIRS
#	List of directories to search for source files. Defaults to
#	$(APP_DIR).
#
# APP_INCLUDE_DIRS
#	List of directories to search for header files. Defaults to
#	$(APP_DIR).
#
# APP_SRCS
#	List of source files to build, relative to $(APP_DIR). Defaults
#	to all .c, .cpp and .S files in $(APP_SRC_DIRS).
#
# May optionally set:
#
# APP_LIBS
#	List of optional libraries to include.
#
# APP_DEFINES
#	USING_OS_FREERTOS : enables FreeRTOS from the SDK
#
