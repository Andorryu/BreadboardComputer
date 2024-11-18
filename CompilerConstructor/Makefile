
all: run

debug: bbc
	gdb ./bbc

run: bbc
	./bbc main.bbc bbc.nfa bbc.sdd

test1: bbc
	./bbc tests/test1.bbc tests/test1.nfa tests/test1.gram 

# test2: bbc
# 	./bbc tests/test2.bbc tests/test2.nfa tests/test2.gram

bbc: *.o
	g++ *.o -g -o bbc

%.o: %.cpp
	g++ -g -c *.cpp

clean:
	rm *.o bbc
