#ifndef SIGNAL
#define SIGNAL

#include "CVector/Vector3.h"
#include "CVector/Quaternion.h"
#include "Robot.h"
#include "Box.h"

class Signal
{
public:
	Vector3 l,dF,dU;
	double distance;

	int type;
	const int* obj;	// a pointer, may be Robot or Box
	int copy(const Robot& x);
	int copy(const Box& x);
	int copy(const Robot& x, double len);
	int copy(const Box& x, double len);
	int turn(const Vector3& _x,const Vector3& _y,const Vector3& _z);
		// calculate relative location, respect to _x as l, _y as dF, _z as dU

	Signal();
	Signal(double x,double y,double z);
	Signal(	double x,double y,double z,
			double a,double b,double c,
			double p,double q,double r);
		// x,y,z location,  a,b,c: front, p,q,r, up

	Signal(const Vector3& _x);
	Signal(	const Vector3& _x,
			const Vector3& _y,
			const Vector3& _z);
	~Signal();
	int commonInit();
};

#endif
