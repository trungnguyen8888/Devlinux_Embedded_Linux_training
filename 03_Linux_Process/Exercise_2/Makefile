CC = gcc
RM = rm -f
SRC := $(wildcard *.c)
TARGET = $(basename $(SRC))

all: $(TARGET)

$(TARGET): $(SRC)
	@echo "Build $(TARGET)"
	$(CC) $(SRC) -o $(TARGET)

clean:
	$(RM) $(TARGET)