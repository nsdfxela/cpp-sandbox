COMMON = ../../common
INC = -I ${COMMON}
CTCH = ${COMMON}/catch

all: triangle.o main.o
	g++ -o triangles.exe main.o triangle.o
main.o: main.cc
	g++ -c -g main.cc
triangle.o: triangle.cc triangle.hpp
	g++ -c -g triangle.cc
clean:
	rm *.o
test: triangles.exe
	cat  ./test1.txt | ./triangles.exe
unit: triangle.o catch.o unit.o 
	g++  -o unit.exe test.o triangle.o catch_amalgamated.o
unit.o: test.cc 
	g++ -c -g ${INC} test.cc 
catch.o: ${CTCH}/catch_amalgamated.cpp ${CTCH}/catch_amalgamated.hpp
	g++ -c -g ${INC}  ${CTCH}/catch_amalgamated.cpp
