checkers.exe: main.o Gameboard.o Game.o 
	g++ -o checkers.exe main.o Gameboard.o Game.o

main.o: main.cpp
	g++ -c main.cpp

Gameboard.o: Gameboard.cpp Gameboard.h
	g++ -c Gameboard.cpp

Game.o: Game.cpp Game.h
	g++ -c Game.cpp

debug:
	g++ -g -o checkerDebug.exe main.cpp Gameboard.cpp Game.cpp

clean:
	rm -f *.exe *.o *.stackdump *~ *.gch

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups