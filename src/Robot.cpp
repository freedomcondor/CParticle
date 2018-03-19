#include "Robot.h"
#include "DirParticle.h"

#define PI 3.1415926535898

Robot::Robot() 
	:DirParticle()
{
	commonInit();
}
Robot::Robot(double x,double y,double z) 
	:DirParticle(x,y,z)
{
	commonInit();
}
Robot::Robot(const Vector3& _x)
	:DirParticle(_x)
{
	commonInit();
}

Robot::Robot(double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r)
	:DirParticle(x,y,z)
{
	commonInit();
}

Robot::Robot(const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z)
	:DirParticle(_x)
{
	commonInit();
}

//DirParticle(const DirParticle& _x);
Robot::~Robot()
{
	//printf("I am the destructor of Robot\n");
}

//////////////////////////////////////////////////////////////////
int Robot::commonInit()
{
	armUpdate();
}

int Robot::armUpdate()
{
	armVec = dF.nor() * armLen;
	Quaternion q;
	q.setFromRotation((dF*dU).nor(),arm*PI/180);
	armVec = q.toRotate(armVec);
}

//////////////////////////////////////////////////////////////////
int Robot::run(double time)
{
	setv(dF.nor() * speed);

	DirParticle::run(time);
	armUpdate();

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
int Robot::setarm(double x)
{
	arm = x;
	return 0;
}
