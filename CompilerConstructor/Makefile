
all: test1 test2

debug: bbc
	gdb ./bbc

test1: bbc
	./bbc test1.bbc

test2: bbc
	./bbc test2.bbc

bbc: *.o
	g++ *.o -g -o bbc

%.o: %.cpp
	g++ -g -c *.cpp

clean:
	rm *.o bbc
