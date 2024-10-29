CC=gcc
CFLAGS=-Wall -Werror -Wextra
BUILD=../build
LIBS=../libs

all: clang main run clean

rebuild: main clean

main: engine.o vector.o player.o main.o
	$(CC) $(CFLAGS) -lncurses vector.o engine.o player.o main.o -o $(BUILD)/exec

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

player.o: player.h player.c
	$(CC) $(CFLAGS) -c player.c

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

