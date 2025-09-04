#================================================================================================
# Start of file																					#
#================================================================================================
#================================================================================================
# Commands																						#
#================================================================================================
CC ?= gcc
RM := rm -rf

#================================================================================================
# Information variables																			#
#================================================================================================
SRC_DIR := src
INC_DIR := include
TARGET  := $(basename $(SRC_DIR))

#================================================================================================
# Compilation flags																				#
#================================================================================================
# Common flags used for static and shared
CFLAGS := -Wall -Wextra -Werror \
          -Wpedantic -pedantic-errors \
          -Wshadow -Wconversion -Wsign-conversion \
          -Wdouble-promotion -Wfloat-equal \
          -Wformat=2 -Wnull-dereference \
          -Wcast-align -Wcast-qual \
          -Wundef -Wstrict-prototypes -Wmissing-prototypes \
          -Wpointer-arith -Wwrite-strings \
          -Wunreachable-code \
          -Wunused -Wunused-parameter -Wunused-but-set-variable \
          -Wlogical-op -Wduplicated-cond -Wduplicated-branches \
          -Wstrict-overflow=5 -Woverflow \
          -Wcast-function-type -Wcast-align=strict \
          -Winline -Wredundant-decls -Wnested-externs \
          -Wformat-truncation=2 -Wformat-overflow=2 \
          -Wstringop-overflow=4 -Wstringop-truncation \
          -Wmissing-noreturn -Wmissing-declarations \
          -Walloca -Walloc-zero \
          -fanalyzer \
          -Og -g \
          -I$(INC_DIR)

#================================================================================================
# Phony targets																					#
#================================================================================================
# Mark these as phony targets so Make won't confuse them with files of the same name
.PHONY: all clean

#================================================================================================
# Targets to build all																			#
#================================================================================================
# Target to build all the targets
all: $(TARGET)

#================================================================================================
# Create necessary folders: libs, build, obj, documents to store generated files				#
#================================================================================================
# Folders that needs to store outputs (libraries, binary, objects)
BUILD_DIR := build
BIN_DIR	  := $(BUILD_DIR)/bin

# Create libs, build, obj
$(BUILD_DIR) $(BIN_DIR):
	@mkdir -p $@

# Targets to create mentioned folders
dir: $(BUILD_DIR) $(BIN_DIR)

#================================================================================================
# Make library																					#
#================================================================================================
# Variables for library
# LIB_NAME := filestat
# LIB_SRC	 := $(wildcard $(SRC_DIR)/*.c)
# LIB_OBJ  := $(OBJ_DIR)/dl_$(LIB_NAME).o
# LIB      := $(LIB_DIR)/lib$(LIB_NAME).a

# # Make dl_filestat.o
# $(LIB_OBJ): $(LIB_SRC) | $(OBJ_DIR)
# 	@mkdir -p $(OBJ_DIR)
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Generate libstrutils.a and remove dl_filestat.o
# $(LIB): $(LIB_OBJ) | $(LIB_DIR)
# 	$(AR) rcs $@ $<
# 	$(RM) $(OBJ_DIR)

#================================================================================================
# Build the application linked with library														#
#================================================================================================
APP		:= main
APP_DIR	:= sample
APP_SRC	:= $(wildcard $(APP_DIR)/*.c)

# Build the application linked with library libstrutils.a
$(TARGET): $(APP_SRC) | $(BIN_DIR)
	@echo "Create executable using static library"
	$(CC) $(CFLAGS) $(APP_SRC) -o $(BIN_DIR)/$(APP)

#================================================================================================
# Remove all outputs																			#
#================================================================================================
clean:
	$(RM) $(BUILD_DIR) $(LIB_DIR)

#================================================================================================
# End of file																					#
#================================================================================================