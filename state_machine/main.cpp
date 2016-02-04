/*
 * main.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: zac
 *     Purpose: This code example shows how a car class has multiple
 *              attributes that are controlled by the car, when it
 *              is ordered into different gears.  This code example
 *              shows our robotics team how to build classes for
 *              actuator groups and shift their state.
 */

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct Car_state{
	int velocity;
	double fuel_air_ratio;
	int rpm;

	Car_state(const int v, const double far, const int r) :
		velocity(v), fuel_air_ratio(far), rpm(r) {}

	friend std::ostream& operator << (std::ostream& os, const Car_state& cs);
};

std::ostream& operator << (std::ostream& os, const Car_state& cs) {
	std::cout<<"The state variables are:\n";
	std::cout<<"\t velocity: "<<cs.velocity<<std::endl;
	std::cout<<"\t fuel air ratio: "<<cs.fuel_air_ratio<<std::endl;
	std::cout<<"\t rpm: "<<cs.rpm<<std::endl;
	return os;
}

class Car {
	/* A car has multiple values associated with each gear.
	 * In this example the operator can shift gears gears of the car,
	 * or change its state, but the car controls all the subsystems
	 * like its fuel burn, velocity, and engine rpm.
	 */
private:
	std::vector<Car_state> states;
	int state_index;	//index of the current state for the Car

	bool state_is_valid() {
		bool res = false;
		if((state_index >=0) && (state_index < states.size())) {
			res = true;
		}
		return res;
	}
	bool index_is_valid(int index) {
		bool res = false;
		if(index>=0 && index<states.size()){
			res = true;
		}
		return res;
	}

public:
	//default constructor
	Car() : state_index(-1) {}

	//add a way to create states for the Car
	void add_state(const Car_state new_state) {
		states.push_back(new_state);
	}
	void add_state(const int v, const double far, const int rpm){
		Car_state temp(v, far, rpm);
		add_state(temp);
	}

	//methods to list the states
	void list_states() {
		for(auto it = states.begin(); it != states.end(); ++it) {
			cout<<*it;
		}
	}

	//see the current state
	void show_state() {
		if (state_is_valid()) {
			cout<<"The car's state is: "<<state_index<<"\n\t";
			std::cout<<states[state_index];
		}
	}

	//find out how many states there are
	int get_states() {
		return states.size();
	}

	//set the Car's state
	bool set_state(int index){
		bool state_is_good = false;
		if(index_is_valid(index)) {
			state_index = index;
			state_is_good = true;
		}
		return state_is_good;
	}
};

int main(int argc, char **argv) {
	Car my_car;

	my_car.add_state(23, 34.56, 23000);
	Car_state cs1 {17, 789.45, 43000};
	my_car.add_state(cs1);
	my_car.add_state(38, 90.3, 56000);

	my_car.list_states();

	my_car.set_state(1);

	my_car.show_state();

	int loop_counter = 0;
	while(loop_counter<3){
		cout<<"\nThe car has "<<my_car.get_states()<<" gears."<<endl;
		cout<<"Select a gear between 0 and "<<my_car.get_states()-1<<": ";
		int gear;
		string line;
		getline(cin, line);
		stringstream ss(line);
		if(ss>>gear){
			if(	! my_car.set_state(gear) )
				cout<<"You requested an invalid gear!\n";
			my_car.show_state();	
		} else
			cout<<"That was invalid input."<<endl;
		
		++loop_counter;	
	}
}





