all: lru.o main.o
	g++ -o app.exe main.o lru.o
main.o: main.cc
	g++ -c -g main.cc
lru.o: lru.h lru.cc
	g++ -c -g lru.cc
clean:
	rm *.o
