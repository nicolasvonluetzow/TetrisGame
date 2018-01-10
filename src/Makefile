CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -I./SDL/include
LFLAGS = -L./SDL/lib -lSDL2main -lSDL2 -lSDL2_image

#Sources
SRC = main.c 
#Headers
HDRS = 
#Kompilierte Exe (T.exe beim Entwickeln, um es schneller eingeben zu koennen)
EXE = T.exe


build: $(EXE)

all: $(EXE)
	./$<

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC) $(LFLAGS)