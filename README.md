# AirportSimpulation
Airport Simulation



Folder:
~This folder contains 4 files in which three are header files and one cpp file

~The airport.h contains runways and airport

~heap.h contains plane and a heap for plane which Sorts on the basis of fuel

~heap1.h contains a min heap

~simulation.cpp is the driver file

~there are also two txt files ie."output.txt" and "file.txt" which are output samples of my code.



Description:
~When the program is run it first asks for the output filename of the format(output.txt)

~Then a .txt file will be made in the project folder

~I have used Structs for planes , runways and airports

~Every plane has an initial time where it entered the queue and an exiting time which it exited and a waiting time ie. the time it had to wait in the queue

~Every plane also has a unit fuel which has a range from 0-10 where 10 is full and 0 is means it has to be landed right now

~The fuel for takeoff is always 10

~Whereas the Fuel for planes coming in for landing is generated by a uniform random number generator

~When the fuel is zero the plane has to land on runway3 which it does.

~The number of planes coming for takeoff or landing is also generated by the uniform random number generator

~The planes first enter the heap and then when its turn comes it is removed from the queue

~I have used priority queues

~My code is well commented

Planeheap:
~My plane heap has the Following Functions:

-decreasefuel(): Which decremnts the fuel of the planes waiting for landing after every simulation time

-getsize():Which returns size of heap

-insert():Which inserts the plane

-remove():Which removes the plane

-getfuel():Which returns the fuel of the top most plane

-print():Which prints the elements of the queue

Minheap:

-insert():inserts a number

-remove():removes the top most number

Output:

~The out put will be of the form of:

-simulation time

-Number of planes coming to land

-Number of planes coming to be takenoff

-The two landing queues of each runway and takeoff queues of every runway

-The description of the plane landed or taken off and the runway on which the action was performed

-The Queues after the action

-The Average landing time

-The Average Takeoff time

-Number of planes landed

-Number of planes Taken off

~The same output will be given for every Simulation time starting from 1

~The output will be for 100 planes landing and 100 planes taken off.





