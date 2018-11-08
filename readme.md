# Checkers AI

A functioning AI for the game checkers.

### Running the program

Make sure all files are downloaded into the proper directory.

Either run the makefile or use the following command:

```
g++ -c main.cpp gameboard.cpp game.cpp
g++ -o checkers.exe main.o Gameboard.o Game.o
./checkers.exe
```

Once finished, follow the instructions the program gives to play.

### Adding new boards

To add new boards use the following board scheme

```
0 - Blank piece
1 - Regular piece for player 1
2 - Regular piece for player 2
3 - King piece for player 1
4 - King piece for player 2
```

An example of the starting board is

```
0 2 0 2 0 2 0 2
2 0 2 0 2 0 2 0
0 2 0 2 0 2 0 2
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
1 0 1 0 1 0 1 0
0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 0
```
