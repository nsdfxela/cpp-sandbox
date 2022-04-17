all: lfu.o cache.o
	g++ -o lfu lfu.o cache.o
lfu.o: lfu.cpp
	g++ -c lfu.cpp
cache.o: cache.hpp cache.cpp
	g++ -c  cache.cpp
clean:
	rm *.o
