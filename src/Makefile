CC=gcc
CFLAGS=-Wall -Werror -Wextra
BUILD=../build

all: clang main run clean

main: main.o engine.o
	$(CC) $(CFLAGS) -lncurses main.o engine.o -o $(BUILD)/exec

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

engine.o: engine.h engine.c
	$(CC) $(CFLAGS) -c engine.c

clang:
	clang-format -i *.c

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

run:
	$(BUILD)/exec

clean:
	rm -rf *.o *.so

