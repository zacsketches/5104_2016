all: threaded_state_machine
	
clean:
	rm *.o threaded_state_machine
	
threaded_state_machine: main.o
	clang++ main.o -o threaded_state_machine
	
main.o: main.cpp
	clang++ -c -std=c++0x main.cpp
	