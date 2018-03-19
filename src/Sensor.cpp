#include "Sensor.h"
#include "DirParticle.h"

#define PI 3.1415926535898

Sensor::Sensor() 
	:DirParticle()
{
	commonInit();
}
Sensor::Sensor(double x,double y,double z) 
	:DirParticle(x,y,z)
{
	commonInit();
}
Sensor::Sensor(const Vector3& _x)
	:DirParticle(_x)
{
	commonInit();
}

Sensor::Sensor(double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r)
	:DirParticle(x,y,z)
{
	commonInit();
}

Sensor::Sensor(const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z)
	:DirParticle(_x)
{
	commonInit();
}

//DirParticle(const DirParticle& _x);
Sensor::~Sensor()
{
	//printf("I am the destructor of Sensor\n");
}


//////////////////////////////////////////////////////////////////
Signal::Signal() 
	:DirParticle()
{
	commonInit();
}
Signal::Signal(double x,double y,double z) 
	:DirParticle(x,y,z)
{
	commonInit();
}
Signal::Signal(const Vector3& _x)
	:DirParticle(_x)
{
	commonInit();
}

Signal::Signal(double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r)
	:DirParticle(x,y,z)
{
	commonInit();
}

Signal::Signal(const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z)
	:DirParticle(_x)
{
	commonInit();
}

//DirParticle(const DirParticle& _x);
Signal::~Signal()
{
	//printf("I am the destructor of Signal\n");
}

//////////////////////////////////////////////////////////////////
int Sensor::commonInit()
{
	n = 0;
}
int Signal::commonInit()
{
}

//////  function  ////////////////////////////////////////////////////////////
///// Signal //////////////////////////////////////////////////

int Signal::copy(const Robot& x)
{
	type = sigRobot;
	obj = &x;
	copyDirP(x);
	return 0;
}

int Signal::copyDirP(const DirParticle& _x)
{
	l = _x.l;
	dF = _x.dF;
	dU = _x.dU;
	return 0;
}

///// Sensor //////////////////////////////////////////////////
int Sensor::sense(const Robot& x)
{
	Signal s;
	s.copy(x);
	n = 1;
	sig[0] = s;
	//sensecheck(s);
	// in rangecheck
	// if in range
		//for search siglist
			// if a hit then update
			// else add
	// else 
		// delete
		
	return 0;
}
int sensecheck(const Signal& x)
{

}
