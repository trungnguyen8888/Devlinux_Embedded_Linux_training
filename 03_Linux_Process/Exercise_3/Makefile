# Compiler and remove command
CC = gcc
RM = rm -f

# List of executables (binary names without extension)
TARGETS = zombie orphan

# Default target
all: $(TARGETS)

# Pattern rule: build each binary from its corresponding .c file
%: %.c
	@echo "Build $@"
	$(CC) $< -o $@

# Clean up all generated binaries
clean:
	$(RM) $(TARGETS)