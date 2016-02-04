all: state_machine
	
clean:
	rm *.o *.out state_machine
	
state_machine: main.o
	clang++ main.o -o state_machine
	
main.o: main.cpp
	clang++ -c -std=c++0x main.cpp
	