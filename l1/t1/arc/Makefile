all: arc.o main.o
	g++ -o arc.exe main.o arc.o
main.o: main.cc
	g++ -c -g main.cc
arc.o: arc.hpp arc.cc
	g++ -c -g arc.cc
clean:
	rm *.o
