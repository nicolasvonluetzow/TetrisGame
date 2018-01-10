CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -I./SDL/include
LFLAGS = -L./SDL/lib -lSDL2main -lSDL2  

#Sources
SRC = main2.c 
#Headers
HDRS = 
#Kompilierte Exe
EXE = TetrisLauncher.exe


build: $(EXE)

all: $(EXE)
	./$<

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC) $(LFLAGS)