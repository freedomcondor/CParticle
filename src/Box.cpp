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

int Box::set(	double x,double y,double z)
{
	DirParticle::set(x,y,z);
	sensorUpdate();
	return 0;
}
int Box::set(	double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r)
{
	DirParticle::set(x,y,z,a,b,c,p,q,r);
	sensorUpdate();
	return 0;
}
int Box::set(	const Vector3& _x)
{
	DirParticle::set(_x);
	sensorUpdate();
	return 0;
}
int Box::set(	const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z)
{
	DirParticle::set(_x,_y,_z);
	sensorUpdate();
	return 0;
}

//----------------------------------------------------------------
int Box::commonInit()
{
	size = 0.1;
	beingcarried = 0;
	fixed = 0;
	ctrl.init((int *)this);
	for (int i = 0; i < 5; i++)
		unsetstig(i);
	stign = 0;

	return 0;
}

int Box::ctrlInit()
{
	ctrl.init((int *)this);
	return 0;
}

int Box::ctrlStoresensor()
{
	ctrl.storesensor();
	return 0;
}

//----------------------------------------------------------------
int Box::run(double time)
{
	ctrl.step(time);
	sensorUpdate();

	DirParticle::run(time);

	return 0;
}


int Box::sensorUpdate()
{
	sensor.set(l,dF,dU);
	return 0;
}

int Box::setstig(int x)	// FRONT, LEFT, BACK ...
{
	stig[x] = 1;
	stign++;
	return 0;
}
int Box::unsetstig(int x)
{
	stig[x] = 0;
	stign--;
	return 0;
}

Vector3 Box::getStigVector(int x) const	//x is FRONT/BACK/...
{
	if (x == FRONT)
		return dF.nor() * size;
	else if (x == BACK)
		return -dF.nor() * size;
	else if (x == UP)
		return dU.nor() * size;
	else if (x == DOWN)
		return -dU.nor() * size;
	else if (x == LEFT)
		return (dU * dF).nor() * size;
	else if (x == RIGHT)
		return (dF * dU).nor() * size;
	else
		return Vector3(0,0,0);
}

int Box::setfix()
{
	fixed = 1;
	return 0;
}
int Box::unsetfix()
{
	fixed = 0;
	return 0;
}
