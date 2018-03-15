#ifndef PARTICLE
#define PARTICLE

#include "CVector/Vector3.h"

class Particle
{
public:
	Vector3 l;
	Vector3 v;
	Vector3 a;

	Particle();
	Particle(double x,double y,double z);
	Particle(const Vector3& _x);
	//Particle(const Particle& _x);
	~Particle();

	int setl(double x,double y,double z);
	int setl(const Vector3& _x);
	int setv(double x,double y,double z);
	int setv(const Vector3& _x);
	int seta(double x,double y,double z);
	int seta(const Vector3& _x);

	int run(double time);
};

#endif
