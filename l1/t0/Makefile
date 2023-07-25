all: lfu.o cache.o
	g++ -o lfu lfu.o cache.o
lfu.o: lfu.cpp
	g++ -c -g lfu.cpp
cache.o: cache.hpp cache.cpp
	g++ -c -g cache.cpp
clean:
	rm *.o
