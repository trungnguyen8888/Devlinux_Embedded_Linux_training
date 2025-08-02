#================================================================================================
# Start of file																					#
#================================================================================================
#================================================================================================
# Commands																						#
#================================================================================================
CC ?= gcc
AR := ar
RM := rm -rf

#================================================================================================
# Folders that store source files and headers													#
#================================================================================================
SRC_DIR := src
INC_DIR := include

#================================================================================================
# Common variables																				#
#================================================================================================
# Variables for library
LIB_NAME := strutils
LIB_SRC	 := $(wildcard $(SRC_DIR)/*.c)

# Variables for application
APP		:= main
APP_DIR	:= sample
APP_SRC	:= $(wildcard $(APP_DIR)/*.c)

#================================================================================================
# Compilation flags																				#
#================================================================================================
# Common flags used for static and shared
CFLAGS := -Wall -Wextra -Werror									\
          -Wpedantic -pedantic-errors							\
          -Wshadow -Wconversion -Wsign-conversion				\
          -Wdouble-promotion -Wfloat-equal						\
          -Wformat=2 -Wnull-dereference							\
          -Wcast-align -Wcast-qual								\
          -Wundef -Wstrict-prototypes -Wmissing-prototypes		\
          -Wpointer-arith -Wwrite-strings						\
          -Wunreachable-code									\
          -Wunused -Wunused-parameter -Wunused-but-set-variable \
          -Wlogical-op -Wduplicated-cond -Wduplicated-branches	\
          -Wstrict-overflow=5 -Woverflow						\
          -Wcast-function-type -Wcast-align=strict				\
          -Winline -Wredundant-decls -Wnested-externs			\
          -Wformat-truncation=2 -Wformat-overflow=2				\
          -Wstringop-overflow=4 -Wstringop-truncation			\
          -Wmissing-noreturn -Wmissing-declarations				\
          -Walloca -Walloc-zero									\
          -fanalyzer											\
          -Og -g												\
          -I$(INC_DIR)


# Flag used to generate shared object shared_dl_strutils.o
PICFLAGS = -fPIC

#================================================================================================
# Phony targets																					#
#================================================================================================
# Mark these as phony targets so Make won't confuse them with files of the same name
.PHONY: all clean static shared dir

#================================================================================================
# Targets to build all																			#
#================================================================================================
# Target to build executable binary files
all: dir static shared

#================================================================================================
# Create necessary folders: libs, build, obj to store generated files							#
#================================================================================================
# Folders that needs to store outputs (libraries, binary, objects)
LIB_DIR	  := libs
BUILD_DIR := build
BIN_DIR	  := $(BUILD_DIR)/bin
OBJ_DIR	  := $(BUILD_DIR)/obj

# Create libs, build, obj
$(LIB_DIR) $(BUILD_DIR) $(BIN_DIR) $(OBJ_DIR):
	@mkdir -p $@

# Targets to create mentioned folders
dir: $(LIB_DIR) $(OBJ_DIR) $(BUILD_DIR) $(BIN_DIR)

#================================================================================================
# Make static library																			#
#================================================================================================
# Variables for static
LIB_STATIC_OBJ := $(OBJ_DIR)/static_dl_$(LIB_NAME).o
LIB_STATIC	   := $(LIB_DIR)/lib$(LIB_NAME).a

# Make static_dl_strutils.o
$(LIB_STATIC_OBJ): $(LIB_SRC) | $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Generate libstrutils.a and remove static_dl_strutils.o
$(LIB_STATIC): $(LIB_STATIC_OBJ) | $(LIB_DIR)
	$(AR) rcs $@ $<
	$(RM) $(OBJ_DIR)

#================================================================================================
# Make shared library																			#
#================================================================================================
# Variables for shared
LIB_SHARED	   := $(LIB_DIR)/lib$(LIB_NAME).so
LIB_SHARED_OBJ := $(OBJ_DIR)/shared_dl_$(LIB_NAME).o

# Make shared_dl_strutils.o
$(LIB_SHARED_OBJ): $(LIB_SRC) | $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@

# Generate libstrutils.so and remove shared_dl_strutils.o
$(LIB_SHARED): $(LIB_SHARED_OBJ) | $(LIB_DIR)
	$(CC) -shared -o $@ $<
	$(RM) $(OBJ_DIR)

#================================================================================================
# Build the application linked with static library												#
#================================================================================================
APP_STATIC_BIN := $(APP)_static

# If in the folder searched, there are both .a and .so, then .so has by default
# the higher priority to be linked with
ifeq ($(wildcard $(LIB_SHARED)),)
	STATIC_LINK_MSG := "No shared library → linking directly with libstrutils.a"
	STATIC_LINK_CMD := $(CC) $(CFLAGS) $(APP_SRC)	\
						-L$(LIB_DIR) -l$(LIB_NAME)	\
						-o $(BIN_DIR)/$(APP_STATIC_BIN)
else
	STATIC_LINK_MSG := "Shared library found → linking directly with static archive (.a)"
	STATIC_LINK_CMD := $(CC) $(CFLAGS) $(APP_SRC) $(LIB_STATIC)		\
						-o $(BIN_DIR)/$(APP_STATIC_BIN)
endif

# Build the application linked with static library libstrutils.a
static: $(LIB_STATIC) | $(BIN_DIR)
	@echo "Create executable using static library"
	@echo $(STATIC_LINK_MSG)
	$(STATIC_LINK_CMD)

#================================================================================================
# Build the application linked with shared library												#
#================================================================================================
APP_SHARED_BIN := $(APP)_shared

# Make sure .so is linked when compiling the app in case there are both .a and .so
# in the folder seached
ifeq ($(wildcard $(LIB_STATIC)),)
	SHARED_LINK_MSG := "No static library → linking directly with libstrutils.so"
	SHARED_LINK_CMD := $(CC) $(CFLAGS) $(APP_SRC)			\
						-L$(LIB_DIR) -l$(LIB_NAME)			\
						-Wl,-rpath,$(abspath $(LIB_DIR))	\
						-o $(BIN_DIR)/$(APP_SHARED_BIN)
else
	SHARED_LINK_MSG := "Static library found → linking directly with static archive (.so)"
	SHARED_LINK_CMD := $(CC) $(CFLAGS) $(APP_SRC) $(LIB_SHARED)		\
						-Wl,-rpath,$(abspath $(LIB_DIR))			\
						-o $(BIN_DIR)/$(APP_SHARED_BIN)
endif

# Build the application linked with shared library libstrutils.so
shared: $(LIB_SHARED) | $(BIN_DIR)
	@echo "Create executable using shared library"
	@echo $(SHARED_LINK_MSG)
	$(SHARED_LINK_CMD)

#================================================================================================
# Remove all outputs																			#
#================================================================================================
clean:
	$(RM) $(BUILD_DIR) $(LIB_DIR)

#================================================================================================
# End of file																					#
#================================================================================================