#include "Box.h"
#include "DirParticle.h"

#define PI 3.1415926535898

Box::Box() 
	:DirParticle()
{
	commonInit();
}
Box::Box(double x,double y,double z) 
	:DirParticle(x,y,z)
{
	commonInit();
}
Box::Box(const Vector3& _x)
	:DirParticle(_x)
{
	commonInit();
}

Box::Box(double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r)
	:DirParticle(x,y,z,a,b,c,p,q,r)
{
	commonInit();
}

Box::Box(const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z)
	:DirParticle(_x,_y,_z)
{
	commonInit();
}

//DirParticle(const DirParticle& _x);
Box::~Box()
{
	ctrl.exit();
	//printf("I am the destructor of Box\n");
}

//////////////////////////////////////////////////////////////////
int Box::commonInit()
{
	size = 0.1;
	ctrl.init((int *)this);

	return 0;
}

int Box::ctrlInit()
{
	ctrl.init((int *)this);
	return 0;
}

//////////////////////////////////////////////////////////////////
int Box::run(double time)
{
	ctrl.step();
	setv(dF.nor() * v.len());

	DirParticle::run(time);

	return 0;
}

int Box::setspeed(double x)
{
	setv(dF.nor() * x);
	return 0;
}
