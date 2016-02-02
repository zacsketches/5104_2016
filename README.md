##Breakerbots
####FRC Team 5104
####Pacific Grove High School
####Pacific Grove, California

##2016 Build Season
This repo contains code used to mentor the Breakerbots as we work our way through the build season this year.

####Proximity Detect
An Arduino sketch used to test the digital output of our proximity sensor we will use to detect the presence of the ball in the robot.

####Concurrency
A C++ program to demonstrate how thread concurrency works so that we can consider multi-threading when the separate components of our robot work together.

####State Machine
We intend to control our robotic assemblies with a state machine.  This is a basic example to show how a class owns its own `vector<allowed_states>` and users interact through the public interface to shift states.
