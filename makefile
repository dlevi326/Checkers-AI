checkers.exe: main.o Gameboard.o Square.o Game.o
	g++ -o Gameboard.exe main.o Square.o Game.o

main.o: main.cpp
	g++ -c main.cpp

Gameboard.o: Gameboard.h Square.h
	g++ -c Gameboard.h

Square.o: Square.h
	g++ -c Square.h

Game.o: Game.h Square.h Gameboard.h
	g++ -c Game.h

debug:
	g++ -g -o gameDebug.exe main.cpp Gameboard.h Square.h Game.h

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups