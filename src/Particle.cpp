//#include <stdio.h>	// for printf

#include "Particle.h"
#include "CVector/Vector3.h"

Particle::Particle()
{
	setl(0,0,0);
}
Particle::Particle(double x,double y,double z)
{
	setl(x,y,z);
}
Particle::Particle(const Vector3& _x)
{
	setl(_x);
}
//Particle(const Particle& _x);
Particle::~Particle()
{
	//printf("I am the destructor of Particle\n");
}

int Particle::setl(double x,double y,double z)
{
	l.x=x;	l.y=y;	l.z=z;
	return 0;
}
int Particle::setl(const Vector3& _x)
{
	l.x=_x.x;	l.y=_x.y;	l.z=_x.z;
	return 0;
}

int Particle::setv(double x,double y,double z)
{
	v.x=x;	v.y=y;	v.z=z;
	return 0;
}
int Particle::setv(const Vector3& _x)
{
	v.x=_x.x;	v.y=_x.y;	v.z=_x.z;
	return 0;
}
int Particle::seta(double x,double y,double z)
{
	a.x=x;	a.y=y;	a.z=z;
	return 0;
}
int Particle::seta(const Vector3& _x)
{
	a.x=_x.x;	a.y=_x.y;	a.z=_x.z;
	return 0;
}

int Particle::run(double time)
{
	l += v * time;
	v += a * time;
	return 0;
}
