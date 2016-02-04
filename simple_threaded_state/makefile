all: state_example
	
clean:
	rm state_example main.o *.out
	
state_example: main.o
	clang++ main.o -o state_example
	
main.o: main.cpp
	clang++ -c -std=c++0x main.cpp