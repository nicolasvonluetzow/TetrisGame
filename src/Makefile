CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -I./SDL/include
LFLAGS = -L./SDL/lib -lSDL2 -lSDL2main 

#Sources
SRC = main.c 
#Headers
HDRS = 
#Name der Exe
EXE = TetrisLauncher.exe


build: $(EXE)

all: $(EXE)
	./$<

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC) $(LFLAGS)