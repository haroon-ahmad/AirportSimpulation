#pragma once
#include <random>
#include "airport.h"
#include "heap1.h"
#include <fstream>
using namespace std;
int main()
{
	//uniform random number generator
	std::random_device rd;
	std::mt19937 gen(rd());

	//landing planes
	plane *p_landing;//pointer of planes 
	int psize_landing=1000;//size of array of the planes
	int currentplane_landing=0;// pointer for the current plane
	p_landing=new plane[psize_landing];//array of the planes

	//takeoff planes
	plane *p_takeoff;//pointer of planes taking off
	int psize_takeoff=1000;//size of array of the planes taking off
	int currentplane_takeoff=0;// pointer for the current plane taking off
	p_takeoff=new plane[psize_takeoff];//array of the planes taking off

	//other variables
	int _id=0;//ids
	airport a;//object of airport which contains three runways
	int simulatontime=1;// system of airport of an hour
	int n_landing;//for number of planes coming
	int n_takeoff;//for number of planes coming for takeoff
	heap size_heap;
	int size1=0;//to get size of heap of runway1
	int size2=0;//to get size of heap of runway2;
	int size3=0;//to get size of third heap of runway3
	int size=0;
	int limit=0;
	plane p1;
	plane p2;
	int planeslanded=0;//number of planes landed
	int planestakenoff=0;//number of planes takenoff
	int operations=0;
	bool r3=false;
	int average=0;

	//timing arrays for landing
	int t_averagetime[500];
	int t_timerpointer=0;

	//timing arrays for takeoff
	int l_averagetime[500];
	int l_timerpointer=0;

	//generating random numbers
	std::uniform_int_distribution<> num_of_planes(0,3);//for number of planes coming for landing
	std::uniform_int_distribution<> _fuel(0,10);
	std::uniform_int_distribution<> _takeoff(simulatontime,simulatontime+10);

	//filing
	char filename[20];
	cout<<"Enter output filename\n";
	cin>>filename;
	ofstream fout;
	fout.open(filename);

	while(planeslanded<100 || planestakenoff<100)
	{
		fout<<"\n-------------------------------------------------------------------simultion time::"<<simulatontime<<"------------------------------------------------------------------------------------------\n\n";
		//Event 1
		//initalizing the new planes coming in for landing
		n_landing=num_of_planes(gen);
		fout<<"number of planes landing:: "<<n_landing<<endl<<endl;
		if(n_landing!=0)
		{
			if(currentplane_landing+n_landing>=psize_landing)
			{
				cout<<"\nFilled\n";
			}
			limit=currentplane_landing+n_landing;
			for(int i=currentplane_landing;i<limit;i++)//loop for the planes coming
			{
				p_landing[i].id=_id;// generates an id of the plane
				_id=_id+2;
				p_landing[i].fuel=_fuel(gen);//generates a random unit for fuel;
				p_landing[i].initial_time=simulatontime;//time the plane entered the queue
				currentplane_landing++;//to make mark of the number of planes to be added

				//adding to heap to find smallest size
				size_heap.insert(a.r1.landing.getsize());
				size_heap.insert(a.r2.landing.getsize());
				size_heap.insert(a.r1.landing2.getsize());
				size_heap.insert(a.r2.landing2.getsize());
				size_heap.remove(size1);
				if(size1==a.r1.landing.getsize())
				{
					a.r1.landing.insert(p_landing[i]);
				}
				else if(size1==a.r2.landing.getsize())
				{
					a.r2.landing.insert(p_landing[i]);
				}
				else if(size1==a.r1.landing2.getsize())
				{
					a.r1.landing2.insert(p_landing[i]);
				}
				else
				{
					a.r2.landing.insert(p_landing[i]);
				}
				size_heap.clearheap();//clears heap
			}
		}

		//Event 2
		//initializing the new planes coming for takeoff
		n_takeoff=num_of_planes(gen);
		fout<<"number of planes taking off:: "<<n_takeoff<<endl<<endl;
		if(n_takeoff!=0)
		{
			if(currentplane_takeoff+n_takeoff>=psize_takeoff)
			{
				cout<<"\nFilled\n";
			}
			limit=n_takeoff+currentplane_takeoff;
			for(int i=currentplane_takeoff;i<limit;i++)//loop for the planes coming
			{
				p_takeoff[i].id=_id;// generates an id of the plane
				_id=_id+2;
				p_takeoff[i].fuel=10;//fuel is full as plane is to be taken off
				p_takeoff[i].time=_takeoff(gen);//time at which plane is to be taken off
				p_takeoff[i].initial_time=simulatontime;
				currentplane_takeoff++;
				//entering into the queue here and incrementing the takeoff start
				size1=a.r1.takeoff.getsize();//getting size of first heap of runway
				size2=a.r2.takeoff.getsize();//getting size of second heap
				size3=a.r3.takeoff.getsize();//getting size of third heap
				//entering the sizes into the heap
				size_heap.insert(size1);
				size_heap.insert(size2);
				size_heap.insert(size3);
				size_heap.remove(size);
				if(size==size1)
				{
					a.r1.takeoff.insert(p_takeoff[i]);
				}
				else if(size==size2)
				{
					a.r2.takeoff.insert(p_takeoff[i]);

				}
				else
				{
					a.r3.takeoff.insert(p_takeoff[i]);
				}
				size_heap.clearheap();

			}
		}
		fout<<"queues Before landing or takeoff:\n\n";
		if(a.r1.landing.getsize()>0)
		{
			fout<<"---------------------runway 1 landing heap----------------------\n"<<endl;
			a.r1.landing.print(fout);
			fout<<endl;
		}
		else
		{
			fout<<"--------First landing queue of Runway1 is Empty\n\n";
		}
		if(a.r1.landing2.getsize()>0)
		{
			fout<<"---------------------runway 1 landing heap2----------------------\n"<<endl;
			a.r1.landing2.print(fout);
			fout<<endl;
		}
		else
		{
			fout<<"-------Second landing queue of Runway1 is Empty\n\n";
		}
		if(a.r2.landing.getsize()>0)
		{
			fout<<"--------------------runway 2 landing heap-------------------------\n"<<endl;
			a.r2.landing.print(fout);
			fout<<endl;
		}
		else
		{
			fout<<"----------First landing queue of Runway2 is Empty\n\n";
		}
		if(a.r2.landing2.getsize()>0)
		{
			fout<<"--------------------runway 2 landing heap2-------------------------\n"<<endl;
			a.r2.landing2.print(fout);
			fout<<endl;
		}
		else
		{
			fout<<"-------Second landing queue of Runway2 is Empty\n\n";
		}
		if(a.r1.takeoff.getsize()>0)
		{
			fout<<"--------------------runway 1 takeoff heap-------------------------\n"<<endl;
			a.r1.takeoff.print(fout);
			fout<<endl;
		}
		else
		{
			fout<<"-------Takeoff queue of Runway1 is Empty\n\n";
		}
		if(a.r2.takeoff.getsize()>0)
		{
			fout<<"---------------------runway 2 takeoff heap-------------------------\n"<<endl;
			a.r2.takeoff.print(fout);
			fout<<endl;
		}
		else
		{
			fout<<"------Takeoff queue of Runway2 is Empty\n\n";
		}
		if(a.r3.takeoff.getsize()>0)
		{
			fout<<"----------------------runway 3 takeoff heap-------------------------\n"<<endl;
			a.r3.takeoff.print(fout);
			fout<<endl;
		}
		else
		{
			fout<<"--------Takeoff queue of Runway3 is Empty\n\n";
		}
		cout<<endl;
		//Event 3
		//landing and takeoff of planes

		//first boundary condition
		if(a.r1.takeoff.getsize()==0 && a.r2.takeoff.getsize()==0 && a.r3.takeoff.getsize()==0)
		{

			if(a.r1.landing.getsize()!=0 || a.r1.landing2.getsize()!=0  )
			{
				if(a.r1.landing.getfuel()==0)
				{
					a.r1.landing.remove(p1);
					a.r3.p=p1;
					a.r3.p.end_time=simulatontime;
					a.r3.p.time=a.r3.p.end_time-a.r3.p.initial_time;
					fout<<"landing at runway 3:\n\n";
					a.r3.p.print(fout);
					l_averagetime[l_timerpointer]=a.r3.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
					r3=true;
				}
				if(a.r1.landing2.getfuel()==0 && r3==false)
				{
					a.r1.landing2.remove(p1);
					a.r3.p=p1;
					a.r3.p.end_time=simulatontime;
					a.r3.p.time=a.r3.p.end_time-a.r3.p.initial_time;
					fout<<"landing at runway 3:\n\n";
					a.r3.p.print(fout);
					l_averagetime[l_timerpointer]=a.r3.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
					r3=true;
				}
				if(a.r1.landing.getsize()>a.r1.landing2.getsize())
				{
					a.r1.landing.remove(p1);
					a.r1.p=p1;
					a.r1.p.end_time=simulatontime;
					a.r1.p.time=a.r1.p.end_time-a.r1.p.initial_time;
					fout<<"landing at runway1:\n\n";
					a.r1.p.print(fout);
					l_averagetime[l_timerpointer]=a.r1.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
				}
				else if(a.r1.landing2.getsize()!=0)
				{
					a.r1.landing2.remove(p1);
					a.r1.p=p1;
					a.r1.p.end_time=simulatontime;
					a.r1.p.time=a.r1.p.end_time-a.r1.p.initial_time;
					fout<<"landing at runway1:\n\n";
					a.r1.p.print(fout);
					l_averagetime[l_timerpointer]=a.r1.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
				}
			}
			if(a.r2.landing.getsize()!=0 || a.r2.landing2.getsize()!=0)
			{
				if(a.r2.landing.getfuel()==0 && r3==false)
				{
					a.r2.landing.remove(p1);
					a.r3.p=p1;
					a.r3.p.end_time=simulatontime;
					a.r3.p.time=a.r3.p.end_time-a.r3.p.initial_time;
					fout<<"landing at runway 3:\n\n";
					a.r3.p.print(fout);
					l_averagetime[l_timerpointer]=a.r3.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
					r3=true;
				}
				if(a.r2.landing2.getfuel()==0 && r3==false)
				{
					a.r2.landing2.remove(p1);
					a.r3.p=p1;
					a.r3.p.end_time=simulatontime;
					a.r3.p.time=a.r3.p.end_time-a.r3.p.initial_time;
					fout<<"landing at runway 3:\n\n";
					a.r3.p.print(fout);
					l_averagetime[l_timerpointer]=a.r3.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
					r3=true;
				}
				if(a.r2.landing.getsize()>a.r2.landing2.getsize())
				{
					a.r2.landing.remove(p2);
					a.r2.p=p2;
					a.r2.p.end_time=simulatontime;
					a.r2.p.time=a.r2.p.end_time-a.r2.p.initial_time;
					fout<<"landing at runway 2:\n\n";
					a.r2.p.print(fout);
					l_averagetime[l_timerpointer]=a.r2.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
				}
				else if(a.r2.landing2.getsize()!=0)
				{

					a.r2.landing2.remove(p2);
					a.r2.p=p2;
					a.r2.p.end_time=simulatontime;
					a.r2.p.time=a.r2.p.end_time-a.r2.p.initial_time;
					fout<<"landing at runway 2:\n\n";
					a.r2.p.print(fout);
					l_averagetime[l_timerpointer]=a.r2.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
				}
			}
		}
		//second boundary condition
		//if landing queues are empty
		else if(a.r1.landing.getsize()==0 && a.r2.landing.getsize()==0 && a.r1.landing2.getsize()==0 && a.r2.landing2.getsize()==0)
		{
			if(a.r1.takeoff.getsize()!=0)
			{
				a.r1.takeoff.remove(p1);
				a.r1.p=p1;
				a.r1.p.end_time=simulatontime;
				a.r1.p.time=a.r1.p.end_time-a.r1.p.initial_time;
				fout<<"Takeoff at runway1:\n\n";
				a.r1.p.print(fout);
				t_averagetime[t_timerpointer]=a.r1.p.time;
				t_timerpointer++;
				planestakenoff++;
				operations++;
			}
			if(a.r2.takeoff.getsize()!=0)
			{
				a.r2.takeoff.remove(p1);
				a.r2.p=p1;
				a.r2.p.end_time=simulatontime;
				a.r2.p.time=a.r2.p.end_time-a.r2.p.initial_time;
				fout<<"Takeoff at runway3:\n\n";
				a.r2.p.print(fout);
				t_averagetime[t_timerpointer]=a.r2.p.time;
				t_timerpointer++;
				planestakenoff++;
				operations++;
			}
			if(a.r3.takeoff.getsize()!=0 && r3==false)
			{
				a.r3.takeoff.remove(p1);
				a.r3.p=p1;
				a.r3.p.end_time=simulatontime;
				a.r3.p.time=a.r3.p.end_time-a.r3.p.initial_time;
				fout<<"Takeoff at runway3:\n\n";
				a.r3.p.print(fout);
				t_averagetime[t_timerpointer]=a.r3.p.time;
				t_timerpointer++;
				planestakenoff++;
				operations++;
			}
		}
		//if everything is normal
		else
		{
			//conditions for runway1
			if(a.r1.landing.getsize()!=0 && a.r1.takeoff.getsize()!=0)
			{
				if(a.r1.landing.getfuel()>4)
				{
					a.r1.takeoff.remove(p1);
					a.r1.p=p1;
					a.r1.p.end_time=simulatontime;
					a.r1.p.time=a.r1.p.end_time-a.r1.p.initial_time;
					fout<<"take off at runway 1:\n\n";
					a.r1.p.print(fout);
					t_averagetime[t_timerpointer]=a.r1.p.time;
					t_timerpointer++;
					planestakenoff++;
					operations++;
				}
				else
				{
					if(a.r1.landing.getfuel()==0)
					{
						a.r1.landing.remove(p1);
						a.r3.p=p1;
						a.r3.p.end_time=simulatontime;
						a.r3.p.time=a.r3.p.end_time-a.r3.p.initial_time;
						fout<<"landing at runway 3:\n\n";
						a.r3.p.print(fout);
						l_averagetime[l_timerpointer]=a.r3.p.time;
						l_timerpointer++;
						planeslanded++;
						operations++;
						r3=true;
					}
					if(a.r1.landing2.getfuel()==0 && r3==false)
					{
						a.r1.landing2.remove(p1);
						a.r3.p=p1;
						a.r3.p.end_time=simulatontime;
						a.r3.p.time=a.r3.p.end_time-a.r3.p.initial_time;
						fout<<"landing at runway 3:\n\n";
						a.r3.p.print(fout);
						l_averagetime[l_timerpointer]=a.r3.p.time;
						l_timerpointer++;
						planeslanded++;
						operations++;
						r3=true;
					}
					if(a.r1.landing.getsize()>a.r1.landing2.getsize())
					{
						a.r1.landing.remove(p1);
						a.r1.p=p1;
						a.r1.p.end_time=simulatontime;
						a.r1.p.time=a.r1.p.end_time-a.r1.p.initial_time;
						fout<<"landing at runway1:\n\n";
						a.r1.p.print(fout);
						l_averagetime[l_timerpointer]=a.r1.p.time;
						l_timerpointer++;
						planeslanded++;
						operations++;
					}
					else if(a.r1.landing2.getsize()!=0)
					{
						a.r1.landing2.remove(p1);
						a.r1.p=p1;
						a.r1.p.end_time=simulatontime;
						a.r1.p.time=a.r1.p.end_time-a.r1.p.initial_time;
						fout<<"landing at runway1:\n\n";
						a.r1.p.print(fout);
						l_averagetime[l_timerpointer]=a.r1.p.time;
						l_timerpointer++;
						planeslanded++;
						operations++;
					}
				}
			}
			else if(a.r1.takeoff.getsize()==0)
			{
				if(a.r1.landing.getfuel()==0)
				{
					a.r1.landing.remove(p1);
					a.r3.p=p1;
					a.r3.p.end_time=simulatontime;
					a.r3.p.time=a.r3.p.end_time-a.r3.p.initial_time;
					fout<<"landing at runway 3:\n\n";
					a.r3.p.print(fout);
					l_averagetime[l_timerpointer]=a.r3.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
					r3=true;
				}
				if(a.r1.landing2.getfuel()==0 && r3==false)
				{
					a.r1.landing2.remove(p1);
					a.r3.p=p1;
					a.r3.p.end_time=simulatontime;
					a.r3.p.time=a.r3.p.end_time-a.r3.p.initial_time;
					fout<<"landing at runway 3:\n\n";
					a.r3.p.print(fout);
					l_averagetime[l_timerpointer]=a.r3.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
					r3=true;
				}
				if(a.r1.landing.getsize()>a.r1.landing2.getsize())
				{
					a.r1.landing.remove(p1);
					a.r1.p=p1;
					a.r1.p.end_time=simulatontime;
					a.r1.p.time=a.r1.p.end_time-a.r1.p.initial_time;
					fout<<"landing at runway1:\n\n";
					a.r1.p.print(fout);
					l_averagetime[l_timerpointer]=a.r1.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
				}
				else if(a.r1.landing2.getsize()!=0)
				{
					a.r1.landing2.remove(p1);
					a.r1.p=p1;
					a.r1.p.end_time=simulatontime;
					a.r1.p.time=a.r1.p.end_time-a.r1.p.initial_time;
					fout<<"landing at runway1:\n\n";
					a.r1.p.print(fout);
					l_averagetime[l_timerpointer]=a.r1.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
				}
			}
			else if(a.r1.landing.getsize()==0 && a.r1.landing2.getsize()==0)
			{
				a.r1.takeoff.remove(p1);
				a.r1.p=p1;
				a.r1.p.end_time=simulatontime;
				a.r1.p.time=a.r1.p.end_time-a.r1.p.initial_time;
				fout<<"takeoff at runway 1:\n\n";
				a.r1.p.print(fout);
				t_averagetime[t_timerpointer]=a.r1.p.time;
				t_timerpointer++;
				planestakenoff++;
				operations++;
			}
			//conditions for runway1 finish here

			// conditions for runway2
			if(a.r2.landing.getsize()!=0 && a.r2.takeoff.getsize()!=0)
			{
				if(a.r2.landing.getfuel()>4)
				{
					a.r2.takeoff.remove(p1);
					a.r2.p=p1;
					a.r2.p.end_time=simulatontime;
					a.r2.p.time=a.r2.p.end_time-a.r2.p.initial_time;
					fout<<"takeoff at runway 2:\n\n";
					a.r2.p.print(fout);
					t_averagetime[t_timerpointer]=a.r2.p.time;
					t_timerpointer++;
					planestakenoff++;
					operations++;
				}
				else
				{
					if(a.r2.landing.getfuel()==0 && r3==false)
					{
						a.r2.landing.remove(p1);
						a.r3.p=p1;
						a.r3.p.end_time=simulatontime;
						a.r3.p.time=a.r3.p.end_time-a.r3.p.initial_time;
						fout<<"landing at runway 3:\n\n";
						a.r3.p.print(fout);
						l_averagetime[l_timerpointer]=a.r3.p.time;
						l_timerpointer++;
						planeslanded++;
						operations++;
						r3=true;
					}
					if(a.r2.landing2.getfuel()==0 && r3==false)
					{
						a.r2.landing2.remove(p1);
						a.r3.p=p1;
						a.r3.p.end_time=simulatontime;
						a.r3.p.time=a.r3.p.end_time-a.r3.p.initial_time;
						fout<<"landing at runway 3:\n\n";
						a.r3.p.print(fout);
						l_averagetime[l_timerpointer]=a.r3.p.time;
						l_timerpointer++;
						planeslanded++;
						operations++;
						r3=true;
					}
					if(a.r2.landing.getsize()>a.r2.landing2.getsize())
					{
						a.r2.landing.remove(p2);
						a.r2.p=p2;
						a.r2.p.end_time=simulatontime;
						a.r2.p.time=a.r2.p.end_time-a.r2.p.initial_time;
						fout<<"landing at runway 2:\n\n";
						a.r2.p.print(fout);
						l_averagetime[l_timerpointer]=a.r2.p.time;
						l_timerpointer++;
						planeslanded++;
						operations++;
					}
					else if(a.r2.landing2.getsize()!=0)
					{

						a.r2.landing2.remove(p2);
						a.r2.p=p2;
						a.r2.p.end_time=simulatontime;
						a.r2.p.time=a.r2.p.end_time-a.r2.p.initial_time;
						fout<<"landing at runway 2:\n\n";
						a.r2.p.print(fout);
						l_averagetime[l_timerpointer]=a.r2.p.time;
						l_timerpointer++;
						planeslanded++;
						operations++;
					}
				}
			}
			else if(a.r2.takeoff.getsize()==0)
			{
				if(a.r2.landing.getfuel()==0 && r3==false)
				{
					a.r2.landing.remove(p1);
					a.r3.p=p1;
					a.r3.p.end_time=simulatontime;
					a.r3.p.time=a.r3.p.end_time-a.r3.p.initial_time;
					fout<<"landing at runway 3:\n\n";
					a.r3.p.print(fout);
					l_averagetime[l_timerpointer]=a.r3.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
					r3=true;
				}
				if(a.r2.landing2.getfuel()==0 && r3==false)
				{
					a.r2.landing2.remove(p1);
					a.r3.p=p1;
					a.r3.p.end_time=simulatontime;
					a.r3.p.time=a.r3.p.end_time-a.r3.p.initial_time;
					fout<<"landing at runway 3:\n\n";
					a.r3.p.print(fout);
					l_averagetime[l_timerpointer]=a.r3.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
					r3=true;
				}
				if(a.r2.landing.getsize()>a.r2.landing2.getsize())
				{
					a.r2.landing.remove(p2);
					a.r2.p=p2;
					a.r2.p.end_time=simulatontime;
					a.r2.p.time=a.r2.p.end_time-a.r2.p.initial_time;
					fout<<"landing at runway 2:\n\n";
					a.r2.p.print(fout);
					l_averagetime[l_timerpointer]=a.r2.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
				}
				else if(a.r2.landing2.getsize()!=0)
				{

					a.r2.landing2.remove(p2);
					a.r2.p=p2;
					a.r2.p.end_time=simulatontime;
					a.r2.p.time=a.r2.p.end_time-a.r2.p.initial_time;
					fout<<"landing at runway 2:\n\n";
					a.r2.p.print(fout);
					l_averagetime[l_timerpointer]=a.r2.p.time;
					l_timerpointer++;
					planeslanded++;
					operations++;
				}
			}
			else if(a.r2.landing.getsize()==0 && a.r2.landing2.getsize()==0)
			{
				a.r2.takeoff.remove(p1);
				a.r2.p=p1;
				a.r2.p.end_time=simulatontime;
				a.r2.p.time=a.r2.p.end_time-a.r2.p.initial_time;
				fout<<"takeoff at runway 2:\n\n";
				a.r2.p.print(fout);
				t_averagetime[t_timerpointer]=a.r2.p.time;
				t_timerpointer++;
				planestakenoff++;
				operations++;
			}
			if(a.r3.takeoff.getsize()!=0 && r3==false)
			{
				a.r3.takeoff.remove(p1);
				a.r3.p=p1;
				a.r3.p.end_time=simulatontime;
				a.r3.p.time=a.r2.p.end_time-a.r2.p.initial_time;
				fout<<"Takeoff at runway 2:\n\n";
				a.r3.p.print(fout);
				t_averagetime[t_timerpointer]=a.r2.p.time;
				t_timerpointer++;
				planestakenoff++;
				operations++;
				r3=true;
			}
		}
		fout<<"\nQueues After landing or takeoff:\n\n";
		if(a.r1.landing.getsize()>0)
		{
			fout<<"------------------runway 1 landing heap------------------\n"<<endl;
			a.r1.landing.print(fout);
			cout<<endl;
		}
		else
		{
			fout<<"-------First Landing queue of Runway1 is Empty\n\n";
		}
		if(a.r1.landing2.getsize()>0)
		{
			fout<<"------------------runway 1 landing heap2------------------\n"<<endl;
			a.r1.landing2.print(fout);
			cout<<endl;
		}
		else
		{
			fout<<"-------Second Landing queue of Runway1 is Empty\n\n";
		}
		if(a.r2.landing.getsize()>0)
		{
			fout<<"-------------------runway 2 landing heap----------------\n"<<endl;
			a.r2.landing.print(fout);
			cout<<endl;
		}
		else
		{
			fout<<"-----First Landing queue of Runway2 is Empty\n\n";
		}
		if(a.r2.landing2.getsize()>0)
		{
			fout<<"-------------------runway 2 landing heap2----------------\n"<<endl;
			a.r2.landing2.print(fout);
			cout<<endl;
		}
		else
		{
			fout<<"------Second Landing queue of Runway2 is Empty\n\n";
		}
		if(a.r1.takeoff.getsize()>0)
		{
			fout<<"-----------------runway 1 takeoff heap-----------------\n"<<endl;
			a.r1.takeoff.print(fout);
			cout<<endl;
		}
		else
		{
			fout<<"------Takeoff queue of Runway1 is Empty\n\n";
		}
		if(a.r2.takeoff.getsize()>0)
		{
			fout<<"---------------runway 2 takeoff heap------------------\n"<<endl;
			a.r2.takeoff.print(fout);
			cout<<endl;
		}
		else
		{
			fout<<"------Takeoff queue of Runway2 is Empty\n\n";
		}
		if(a.r3.takeoff.getsize()>0)
		{
			fout<<"----------------runway 3 takeoff heap----------------"<<endl;
			a.r3.takeoff.print(fout);
			cout<<endl;
		}
		else
		{
			fout<<"-------Takeoff queue of Runway3 is Empty\n\n";
		}
		cout<<endl;
		r3=false;
		a.r1.landing.decreasefuel();
		a.r2.landing.decreasefuel();
		a.r1.landing2.decreasefuel();
		a.r2.landing2.decreasefuel();
		simulatontime++;
		for(int i=0;i<l_timerpointer;++i)
		{
			average=average+l_averagetime[i];
		}
		if(l_timerpointer!=0)
			fout<<"\n Average landing time is:: "<<average/l_timerpointer<<endl;
		else
			fout<<"\n Average landing time is:: "<<"0"<<endl;
		average=0;
		for(int i=0;i<t_timerpointer;++i)
		{
			average=average+t_averagetime[i];
		}
		if(t_timerpointer!=0)
			fout<<"\n Average takeoff time is:: "<<average/t_timerpointer<<endl;
		else
		{
			fout<<"\n Average takeoff time is:: "<<"0"<<endl;
		}
		fout<<"\n NUMBER OF PLANES LANDED ::"<<planeslanded<<endl;
		fout<<"\n NUMBER OF PLANES TAKEN OFF::"<<planestakenoff<<endl<<endl;
		//fout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
		//fout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
		fout<<"__________________________________________________________________________________________________________________________________________________________________"<<endl<<endl;
		fout<<"__________________________________________________________________________________________________________________________________________________________________"<<endl<<endl;
	}

	return 0;
}