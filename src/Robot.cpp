#include "Robot.h"
#include "DirParticle.h"

#define PI 3.1415926535898

Robot::Robot() 
	:DirParticle()
{
	setdF(1,0,0); setdU(0,0,1);
	setw(0,0,0); setwa(0,0,0);
	speed = 0;
}
Robot::Robot(double x,double y,double z) 
	:DirParticle(x,y,z)
{
	setdF(1,0,0); setdU(0,0,1);
	setw(0,0,0); setwa(0,0,0);
	speed = 0;
}
Robot::Robot(const Vector3& _x)
	:DirParticle(_x)
{
	setdF(1,0,0); setdU(0,0,1);
	setw(0,0,0); setwa(0,0,0);
	speed = 0;
}

Robot::Robot(double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r)
	:DirParticle(x,y,z)
{
	setdF(a,b,c); setdU(p,q,r);
	setw(0,0,0); setwa(0,0,0);
	speed = 0;
}

Robot::Robot(const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z)
	:DirParticle(_x)
{
	setdF(_y); setdU(_z);
	setw(0,0,0); setwa(0,0,0);
	speed = 0;
}

//DirParticle(const DirParticle& _x);
Robot::~Robot()
{
	//printf("I am the destructor of Robot\n");
}

//////////////////////////////////////////////////////////////////
int Robot::run(double time)
{
	setv(dF.nor() * speed);
	DirParticle::run(time);
	return 0;
}
int Robot::setspeed(double x)
{
	speed = x;
	return 0;
}
int Robot::setturn(double x)	// x in degree
{
	setw(Vector3(0,0,1)*x*PI/180);
	return 0;
}
