#ifndef AIRPORT_HEADER
#define AIRPORT_HEADER
#include "heap.h"

struct runway1
{
	plane p;//id of the plane landing or takingoff
	planeheap takeoff;// queue for takeoff
	planeheap landing2;
	planeheap  landing;
};
struct runway2
{
	plane p;//id of the plane landing or takingoff
	planeheap takeoff;// queue for takeoff
	planeheap landing2;
	planeheap  landing;
};

struct runway3
{
	plane p;//id of the plane landing or takingoff
	planeheap takeoff;// queue for takeoff
};
struct  airport
{
	runway1 r1;
	runway2 r2;
	runway3 r3;
};
#endif