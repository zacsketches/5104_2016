/* This program is intended to show how the main program continues
 * to run at 4hz while the threaded piece completes is work over time
 * and reports back so the main thread can take an action.
*/

#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

using namespace std::chrono;
using namespace std;
using chrono::milliseconds;


mutex cout_mutex;
const double main_duration = 5000;	// ms

void main_feedback(){
	unique_lock<mutex> lck{cout_mutex};
	cout<<"Main feedback"<<endl;
}

void task_feedback() {
	unique_lock<mutex> lck{cout_mutex};
	cout<<"\t\t\t\tTask feedback"<<endl;
}



void task() {
	//take some time and then report completion via a condition variable
	task_feedback();	
}


bool loop_complete(const steady_clock::time_point& t0) {
	bool result = false;
	auto t1 = steady_clock::now();
	auto span = t1-t0;
	if(duration_cast<milliseconds>(t1-t0).count() > main_duration) 
		result = true;
	return result;
}

int main (int argc, char  *argv[])
{
	//1. Enter a 4hz while loop for five seconds
	//2. Launch the task just once
	//3. Feedback to cout
	
	//loop control varibles
	auto t0 = steady_clock::now();	//time start for the loop
	bool task_started = false;		//task launch control
	
	//container for the thread
	thread outer;
	
	while(true){
		main_feedback();
		
		if(!task_started) {
			task_started=true;
			thread th1{task};
			outer = move(th1);
//			t1.detach();
		}
				
		if(loop_complete(t0)) break;
		this_thread::sleep_for(milliseconds(250));
	}
	
	outer.join();
	
	return 0;
}