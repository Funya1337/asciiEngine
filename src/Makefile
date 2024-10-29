CC=gcc
CFLAGS=-Wall -Werror -Wextra
BUILD=../build
LIBS=../libs

all: clang main run clean

rebuild: main clean

main: main.o engine.o vector.o
	$(CC) $(CFLAGS) -lncurses vector.o main.o engine.o -o $(BUILD)/exec

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

engine.o: engine.h engine.c
	$(CC) $(CFLAGS) -c engine.c

vector.o: $(LIBS)/vector.c $(LIBS)/vector.h
	$(CC) $(CFLAGS) -c $(LIBS)/vector.c

clang:
	clang-format -i *.c

leaks: rebuild
	leaks -atExit -- $(BUILD)/exec

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

run:
	$(BUILD)/exec

clean:
	rm -rf *.o *.so

