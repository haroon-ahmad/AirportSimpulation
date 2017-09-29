#pragma once
#include <iostream>
using namespace std;
#include <fstream>
struct plane
{
	int id;//id of plane
	int fuel;// fuel left range from 10 - 0 where 0 means fuel is finished
	int initial_time;//time when entered in queue
	int end_time;//when plane landed
	int time;//time the plane had to wait in the queue
	void print(ofstream& fout)
	{
		fout<<"id : "<<id<<" "<<"fuel : "<<fuel<<" "<<"initialtime : "<<initial_time<<" "<<"End time : "<<end_time<<" "<<"total time waited : "<<time<<" "<<endl<<endl;
	}
};
class planeheap
{
private:
	plane *arr;
	int last;
	int size;
public:
	planeheap();
	planeheap(int const &size);
	int getsize();
	planeheap(const planeheap & _h);
	planeheap& operator=( const planeheap& _h);
	void insert(const plane &num);
	plane* remove(plane &num);
	int getfuel();
	void print(ofstream& fout);
	void decreasefuel();
	~planeheap();
};
planeheap::planeheap()
{
	size=500;
	last=0;
	arr=new plane[size];

}
planeheap::planeheap(int const &size)
{
	this->size=size;
	last=0;
	arr=new plane[this->size];
}
int planeheap::getsize()
{
	return last;
}
planeheap::planeheap(const planeheap & _h)
{
	size=_h.size;
	last=_h.last;
	for(int i=0;i<last;i++)
	{
		this->arr[i].id=_h.arr[i].id;
		this->arr[i].fuel=_h.arr[i].fuel;
		this->arr[i].time=_h.arr[i].time;
	}
}
planeheap& planeheap::operator=( const planeheap& _h)
{
	if (this==&_h) 
		return *this;
	else
	{
		delete[]arr;
		size=_h.size;
		last=_h.last;
		for(int i=0;i<last;i++)
		{
			arr[i].id=_h.arr[i].id;
			arr[i].fuel=_h.arr[i].fuel;
			arr[i].time=_h.arr[i].time;
		}
		return *this;
	}
}
void planeheap::insert(const plane &num)
{
	if(last==size)
	{
		cout<<"Heap is filled";
	}

	last++;
	int i;
	for(i=last;true;)
	{
		if(i==1)
			break;
		if(num.fuel>arr[i/2].fuel)
			break;
		arr[i]=arr[i/2];
		i=i/2;
	}
	arr[i]=num;


}
plane* planeheap::remove(plane &num)
{
	int i=1;
	if(last==0)return nullptr;
	else
	{
		num=arr[i];
		plane k=arr[last--];
		for(int j=2;j<=last;)
		{
			if(j<last)
			{
				if(arr[j].fuel>arr[j+1].fuel)j++;
			}
			if(k.fuel<=arr[j].fuel)break;
			arr[i]=arr[j];
			i=j;
			j=j*2;
		}
		arr[i]=k;
	}
}
void planeheap::print(ofstream& fout)
{
	for(int i=1;i<=last;i++)
		fout<<"Node "<<i<<" "<<"id: "<<arr[i].id<<" "<<"fuel: "<<arr[i].fuel<<" "<<"initialtime: "<<arr[i].initial_time<<endl<<endl;
}
planeheap::~planeheap()
{
	delete [] arr;
	size=0;
	last=0;
}
int planeheap::getfuel()
{
	return arr[1].fuel;
}
void planeheap::decreasefuel()
{
	for(int i=1;i<=last;i++)
	{
		arr[i].fuel--;
	}
}