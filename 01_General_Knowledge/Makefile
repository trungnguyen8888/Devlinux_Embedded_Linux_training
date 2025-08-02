CC = gcc
AR = ar
RM = rm -f
SRC := $(wildcard *.c)

all: static shared

static:
	@echo "Create executable using static library"
	$(CC) -c bstrutils.c -o static_strutils.o
	$(AR) rcs libstrutils.a static_strutils.o
	$(CC) main.c -L. -lstrutils -o main_static

shared:
	@echo "Create executable using shared library"
	$(CC) -fPIC -c bstrutils.c -o shared_strutils.o
	$(CC) -shared -o libstrutils.so shared_strutils.o
	$(CC) main.c -L. -lstrutils -o main_shared

clean:
	$(RM) *.o *.a *.so main_*