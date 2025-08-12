CC = gcc
RM = rm -f
SRC := $(wildcard *.c)
TARGET := app

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	@echo "Build $@"
	$(CC) -Wall -Wextra -pthread $(SRC) -o $@

clean:
	$(RM) $(TARGET)

# This portion is just for building documents for the answers.
# Please make sure you have installed required dependencies for building AsciiDoctor files
# ADOC_COMPILER = asciidoctor
# DOC := $(wildcard *.adoc)

# all_doc: pdf html

# html:
# 	$(ADOC_COMPILER) $(DOC)

# pdf:
# 	$(ADOC_COMPILER)-$@ $(DOC)
# End of document building