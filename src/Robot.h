#ifndef ROBOT
#define ROBOT

#include "DirParticle.h"
#include "LuaController.h"

class Robot	: public DirParticle
{
public:
	double speed = 0;	// the speed toward front(dirFront or dF)
	double arm = 0;		// in degree
	Vector3 armVec;
	double size = 0.1;
	double armLen = size;
	int armUpdate();

	LuaController ctrl;
	int ctrlInit();	
		// in have to call this in main,(like a.ctrlInit) after construct
		// otherwise it is the constructor it pushed in lua

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
	int commonInit();
	//Particle(const Particle& _x);
	~Robot();

	int run(double time);
	int setspeed(double x);
	int setturn(double x);
	int setarm(double x);	// in degree  0-90
};

#endif
