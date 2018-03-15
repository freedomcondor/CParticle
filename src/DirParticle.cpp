//#include <stdio.h>	// for printf

#include "DirParticle.h"
#include "CVector/Vector3.h"
#include "CVector/Quaternion.h"

DirParticle::DirParticle() 
	:Particle()
{
	setdF(1,0,0); setdU(0,0,1);
	setw(0,0,0); setwa(0,0,0);
}
DirParticle::DirParticle(double x,double y,double z) 
	:Particle(x,y,z)
{
	setdF(1,0,0); setdU(0,0,1);
	setw(0,0,0); setwa(0,0,0);
}
DirParticle::DirParticle(const Vector3& _x)
	:Particle(_x)
{
	setdF(1,0,0); setdU(0,0,1);
	setw(0,0,0); setwa(0,0,0);
}

DirParticle::DirParticle(double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r)
	:Particle(x,y,z)
{
	setdF(a,b,c); setdU(p,q,r);
	setw(0,0,0); setwa(0,0,0);
}

DirParticle::DirParticle(const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z)
	:Particle(_x)
{
	setdF(_y); setdU(_z);
	setw(0,0,0); setwa(0,0,0);
}

//Particle(const Particle& _x);
DirParticle::~DirParticle()
{
	//printf("I am the destructor of DirParticle\n");
}

///////////////////////////////////////////////////////////
int DirParticle::setdF(double x,double y,double z)
{
	dF.x=x;	dF.y=y;	dF.z=z;
	return 0;
}
int DirParticle::setdF(const Vector3& _x)
{
	dF.x=_x.x;	dF.y=_x.y;	dF.z=_x.z;
	return 0;
}

int DirParticle::setdU(double x,double y,double z)
{
	dU.x=x;	dU.y=y;	dU.z=z;
	return 0;
}
int DirParticle::setdU(const Vector3& _x)
{
	dU.x=_x.x;	dU.y=_x.y;	dU.z=_x.z;
	return 0;
}

int DirParticle::setw(double x,double y,double z)
{
	w.x=x;	w.y=y;	w.z=z;
	return 0;
}
int DirParticle::setw(const Vector3& _x)
{
	w.x=_x.x;	w.y=_x.y;	w.z=_x.z;
	return 0;
}

int DirParticle::setwa(double x,double y,double z)
{
	wa.x=x;	wa.y=y;	wa.z=z;
	return 0;
}
int DirParticle::setwa(const Vector3& _x)
{
	wa.x=_x.x;	wa.y=_x.y;	wa.z=_x.z;
	return 0;
}

int DirParticle::run(double time)
{
	Particle::run(time);

	Quaternion q;
	q.setFromRotation(w,w.len()*time);
	dF = q.toRotate(dF);
	dU = q.toRotate(dU);

	w += wa * time;
	return 0;
}
