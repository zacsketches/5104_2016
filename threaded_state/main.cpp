/*This example file is intended to explore feedback from a state machine that
 * takes some time to complete the transition between states
*/

#include <iostream>
#include <chrono>
#include <thread>

class Relay{
public:
	enum Relay_state{off, on};
private:
	int ch;
	int st;
	
public:
	Relay(int channel, Relay_state state=Relay_state::off) : ch(channel), st(state) {}
	void set(Relay_state state){
		st = state;
	}
	void turn_on() {
		set(Relay_state::on);
	}
	void turn_off() {
		set(Relay_state::off);
	}
};

class TalonSRX{
	int ch;
	double control_effort; //bounded from [-1:1]
	static const double max = 1.0;
	static const double min = -1.0;
	
	bool effort_is_valid(double new_effort) {
		bool result = false;
		if (new_effort>=min && new_effort<=max) 
			result = true;
		return result;
	}
	
public:
	void set(double effort) {
		if(effort_is_valid) 
			control_effort = effort;
	}
	double effort() { return control_effort; }
};

typedef Relay Spike;

class Roller{
	//contoller
	Spike spike;
	
public:
	void activate() {
		spike.turn_on();
	}
	void deactivate() {
		spike.turn_off();
	}
};

class Elbow{
	//controller
	TalonSRX talon;
	double pos;	//angualar meausure in radians. 0.0 is at forward limit.
	static const double max_position = 2.0;
	static const double min_position = 0.0;
	
public:
	void set_position(double new_position){
		//if the ordered position is legal then execute the control code 
		//in the brackets to get it there.
		if(position_is_valid(new_position)){
			vhile(new_posiiton >= pos) {
				//move towards a higher position
				talon.set(.75);
			}
			else {
				//move towards a lower position
			}
		}
	}
	void position() { return pos; } 
	
};

class Arm{
	Roller roller;
	Elbow elbow;
};

int main (int argc, char  *argv[])
{
	
	return 0;
}