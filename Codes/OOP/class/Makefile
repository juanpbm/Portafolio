all :main



main:ZedBoard.o main.o 
	g++ ZedBoard.o main.o -o main -Wall -Werror



ZedBoard.o:ZedBoard.h ZedBoard.cc
	g++ -c ZedBoard.cc -Wall -Werror


main.o:main.cc
	g++ -c main.cc -Wall -Werror


clear: 
	rm *.o main
