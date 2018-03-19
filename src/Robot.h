#ifndef ROBOT
#define ROBOT

#include "DirParticle.h"

class Robot	: public DirParticle
{
public:
	double speed;	// the speed toward front(dirFront or dF)

	Robot();
	Robot(double x,double y,double z);
	Robot(	double x,double y,double z,
			double a,double b,double c,
			double p,double q,double r);
		// x,y,z location,  a,b,c: front, p,q,r, up

	Robot(const Vector3& _x);
	Robot(	const Vector3& _x,
			const Vector3& _y,
			const Vector3& _z);
	//Particle(const Particle& _x);
	~Robot();

	int run(double time);
	int setspeed(double x);
	int setturn(double x);
};

#endif
