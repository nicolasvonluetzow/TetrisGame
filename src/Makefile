CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra
#math.h
LDFLAGS = -lm

all: TetrisLauncher.exe
	TetrisLauncher.exe


%.o:%.c tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

	
TetrisLauncher.exe: main.o  tetris.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 
