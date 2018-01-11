# Prozedurale Programmierung Projektplanung - �Tetris�

## Spezifikationen 

Angelehnt an die erste ver�ffentlichte Version von Tetris:

* Es fallen dauerhaft neue Bl�cke, mit 7 verschiedenen Formen, in das Spielfeld hinein.
  * Die Bl�cke k�nnen w�hrend des Fallens seitlich bewegt und rotiert werden.
  * Bei Dr�cken der unteren Bewegungstaste wird der Block automatisch unten an der gerade ausgew�hlten Stelle platziert.

* Ist eine Reihe des Spielfelds komplett durch Bl�cke bedeckt so verschwindet diese Reihe (maximal 4 Reihen gleichzeitig m�glich).

* Ziel des Spiels ist es, durch das Verschwinden daf�r zu sorgen, dass die Bl�cke nicht zu hoch gestapelt werden.
  * Wird ein Block nicht (komplett) innerhalb des Spielfelds platziert, wird das Spiel beendet. (Game Over)
  * Ein Ende des Spieles ist per se nicht zu erreichen, der Fortschritt wird durch ein Score-System dargestellt.

* Das Score System:
  * Jede fertiggestellte Reihe bringt Punkte auf den Score. 
  * Mehrere Reihen, die gleichzeitig fertiggestellt werden, geben einen h�heren Wert auf den Score, als wenn diese Reihen einzeln fertiggestellt worden.
  * 4 gleichzeitig fertiggestellte Reihen ergeben einen sog. �Tetris� und damit einen gr��eren Bonus auf den Score.

* Die Standardgeschwindigkeit der fallenden Bl�cke ergibt sich durch das aktuelle Level. Hierbei gibt es in der Theorie kein maximales Level.
  * Jede fertiggestellte Reihe erh�ht den Fortschritt des Levels. (Ein Tetris erh�ht den Fortschritt deutlich st�rker, dieses System ist unabh�ngig von dem Score.)
	

## Design
### (i) Programmstruktur
Die wichtigste Funktion des Programmes ist die `tick()` Methode, welche jeden Tick des Spiels aufgerufen wird, es sei denn es wurde noch nicht gestartet oder bereits beendet. 
In der Hauptstruktur `struct tetrisGame{}` befinden sich die gesamten Daten zum Spiel. Diese reichen von der Map, mit Zeilen und Spaltenanzahl, Score, Level, 
bis zum gerade fallenden Block sowie dem n�chsten Block.
Verliert der Spieler, so wird ein �Game Over� - Fenster angezeigt, welches auch den erreichten Score enth�lt. Aus diesem Fenster kann dann das Spiel beendet werden.

### (ii) wichtige Methoden
#### Wird jeden Tick aufgerufen. Ruft andere Methoden zum anzeigen und berechnen des Spiels auf.
``` c
void tick();
```

#### Wendet die Gravitation auf das momentane Feld an.
``` c
void applyGravity(tetrisGame *game);
```

#### Checkt ob eine Reihe komplett mit Bl�cken bedeckt ist.
``` c
void checkRows(tetrisGame *game);
```

#### Generiert den n�chsten zu platzierenden Block.
``` c
void generateNext(tetrisGame *game);
```


### (iii) zentrale Strukturen
#### Hauptstruktur, enth�lt die Map, die Zeilen-/Spaltenanzahl, den Score, Anstieg zum n�chsten Level und den aktuellen, sowie den n�chsten Block.
``` c
struct tetrisGame { 
  int rows; 
  int columns; 
  char *map; 
  int score; 
  int level; 
  int linesToNextLevel; 
  struct block falling; 
  struct block next;
};
```

#### Struktur f�r einen Block. Enth�lt die Blockart, die Rotation und die Position.
``` c
struct block { 
  int type; 
  int orientation; 
  struct position pos; 
};
```

#### Struktur f�r Positionen.
``` c
struct position { 
  int x; 
  int y; 
};
```