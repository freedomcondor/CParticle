#ifndef BOX
#define BOX

#include "DirParticle.h"
#include "LuaController.h"

class Box	: public DirParticle
{
public:
	double size;

	BoxController ctrl;
	int ctrlInit();	
		// in have to call this in main,(like a.ctrlInit) after construct
		// otherwise it is the constructor it pushed in lua

	Box();
	Box(double x,double y,double z);
	Box(	double x,double y,double z,
			double a,double b,double c,
			double p,double q,double r);
		// x,y,z location,  a,b,c: front, p,q,r, up

	Box(const Vector3& _x);
	Box(	const Vector3& _x,
			const Vector3& _y,
			const Vector3& _z);
	int commonInit();
	//Particle(const Particle& _x);
	~Box();

	int run(double time);
	int setspeed(double x);
};

#endif
