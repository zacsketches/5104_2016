#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>

using namespace std;

mutex cout_mutex;

struct Whistle{
	mutex wm;
	Whistle() {}
	void operator() (){
		cout<<"Blowing the whistle"<<endl;
	}
	void blow() {
		cout<<"Manually blowing the whistle"<<endl;
	}
};

void pause_thread(int sec) {
	cout<<"thread started\n";
	this_thread::sleep_for(chrono::seconds(sec));
	cout<<"thread sleep completed after "<<sec<<" seconds."<<endl;
}

void pause_with_ID(int sec, int ID) {
	cout<<"thread "<<ID<<" started"<<endl;
	this_thread::sleep_for(chrono::seconds(sec));
	cout<<"thread sleep completed after "<<sec<<" seconds."<<endl;
	
}

void pause_with_wp(int sec, Whistle* wp) {
	wp->blow();
	this_thread::sleep_for(chrono::seconds(sec));
	cout<<"thread sleep completed after "<<sec<<" seconds."<<endl;	
}

void pause_with_wp_mutex(int sec, Whistle* wp) {
	/*before we blow the whistle we get the mutex from the whistle.
	 * if we are holding the mutex then no one else can have it. Then
	 * we make sure all the code that blows the whistle has the mutex
	 * before blowing.
	*/
	unique_lock<mutex> lck{wp->wm};	//acquire whistle's mutex
	wp->blow();
	lck.unlock();
	
	this_thread::sleep_for(chrono::seconds(sec));
	cout<<"thread sleep completed after "<<sec<<" seconds."<<endl;
}

void pause_with_id_mutex(int sec, Whistle* wp, int ID) {
	/*before we blow the whistle we get the mutex from the whistle.
	 * if we are holding the mutex then no one else can have it. Then
	 * we make sure all the code that blows the whistle has the mutex
	 * before blowing.
	*/
	unique_lock<mutex> lck{wp->wm};	//acquire whistle's mutex
	wp->blow();
	lck.unlock();
	
	this_thread::sleep_for(chrono::seconds(sec));
	
	//before we use cout we acquire the mutex for cout
	unique_lock<mutex> cout_lck{cout_mutex};
	cout<<"thread "<<ID<<" sleep completed after "<<sec<<" seconds."<<endl;
	//the cout_lck object impicitlye unlocks the mutex upon exiting the
	//function
}

void wait(int sec) {
	cout<<endl;
	this_thread::sleep_for(chrono::seconds(sec));
}

//default wait of 10 sec
void wait() {
	cout<<endl;
	this_thread::sleep_for(chrono::seconds(10));
}

//pause for user
void user() {
	string line;
	cout<<"--Press 'Enter' to continue:";
	getline(cin, line);
	cout<<endl;
}

int main (int argc, char  *argv[])
{
	cout<<"\nThis program demonstrates threads and some ways to do simple\n"
		<<"parallel processing.\n";
	user();
		
	cout<<"We start by creating a pointer to a Whistle opbject and as you \n"
		<<"would expect the only function of a Whistle is to blow it which\n"
			<<"looks like this: "<<endl;
	wait(2);
	Whistle* wp = new Whistle();
	wp->blow();
	
	wait(2);
	cout<<"Pretty simple, right.  Okay let's get started\n";
	user();
	
	cout<<"We begin by firing up two threads.  One runs for 1 secondd and the\n"
		<<"other runs for two seconds, like this."<<endl;
	wait(3);
	thread t1 {pause_thread, 1};
	thread t2 {pause_thread, 2};
	t1.join();
	t2.join();
	wait(2);
	cout<<"That's weird, isn't it?  Why did the 'thread started' output\n"
		<<"look so garbled"<<endl;
	wait(3);
	user();

	cout<<"Next we fire up two more threads, but these thread have an id\n"
		<<"Number assigned to them.  It looks like this:"<<endl;
	wait(3);
	thread t3 {pause_with_ID, 1, 3};
	thread t4 {pause_with_ID, 2, 4};
	t3.join();
	t4.join();
	wait(2);
	cout<<"This time our well behaved threads report their ID, and their status\n"
		<<" and then complete"<<endl;
	wait(3);
	user();

	cout<<"This section shows how to pass a pointer to the Whistle\n"
		<<"into a new thread of execution.  But you will notice that when\n"
		<<"each thread blows the whistle the output is not what we want.\n"
		<<"the two threads are stepping on each other and causing an\n"
		<<"unpredictable output.\n";
	wait(5);
	thread t5 {pause_with_wp, 1, wp};
	thread t6 {pause_with_wp, 2, wp};
	t5.join();
	t6.join();
	wait(2);
	cout<<"Wow...that is messy.  Make sure you understand the error before\n"
		<<"moving on."<<endl;
	wait(3);
	user();
	
	cout<<"We solve this by using the Mutex inside the Whistle.\n";
	wait(2);
	thread t7 {pause_with_wp_mutex, 1, wp};
	thread t8 {pause_with_wp_mutex, 1, wp};
	t7.join();
	t8.join();
	wait(3);
	cout<<"hmmmmm....still not right.  This time we were able to lock the\n"
		<<"whistle, but because both threads slept for the same 1 second it\n"
		<<"they had a data race on cout.  Looks like we may need to create a\n"
		<<"mutex for that too!"<<endl;
	wait(3);
	user();
	
	cout<<"In the final example we use the global mutex cout_mutex to control\n"
		<<"access to std out.";
	wait(2);
	thread t9 {pause_with_id_mutex, 1, wp, 9};
	thread t10 {pause_with_id_mutex, 1, wp, 10};
	t9.join();
	t10.join();
	wait(3);
	cout<<"Cool!!!"<<endl;
	wait(3);
	user();
		
	cout<<"\nAll threads complete. \nNOW GO MAKE SURE YOU UNDERSTAND THE CODE! ;-)\n\n"<<endl;
	
	delete wp;
	return 0;
}