#include "Robot.h"
#include "Box.h"
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
	:DirParticle(x,y,z,a,b,c,p,q,r)
{
	commonInit();
}

Robot::Robot(const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z)
	:DirParticle(_x,_y,_z)
{
	commonInit();
}

//DirParticle(const DirParticle& _x);
Robot::~Robot()
{
	ctrl.exit();
	//printf("I am the destructor of Robot\n");
}

int Robot::set(	double x,double y,double z)
{
	DirParticle::set(x,y,z);
	armUpdate();
	sensorUpdate();
	return 0;
}
int Robot::set(	double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r)
{
	DirParticle::set(x,y,z,a,b,c,p,q,r);
	armUpdate();
	sensorUpdate();
	return 0;
}
int Robot::set(	const Vector3& _x)
{
	DirParticle::set(_x);
	armUpdate();
	sensorUpdate();
	return 0;
}
int Robot::set(	const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z)
{
	DirParticle::set(_x,_y,_z);
	armUpdate();
	sensorUpdate();
	return 0;
}

//////////////////////////////////////////////////////////////////
int Robot::commonInit()
{
	speed = 0;	// the speed toward front(dirFront or dF)
	arm = 0;		// in degree
	size = 0.1;
	armLen = size/2;
	carrying = NULL;

	ctrl.init((int *)this);
	armUpdate();
	sensorUpdate();

	return 0;
}

int Robot::ctrlInit()
{
	ctrl.init((int *)this);
	return 0;
}

int Robot::armUpdate()
{
	armVec = dF.nor() * armLen;
	Quaternion q;
	q.setFromRotation((dF*dU).nor(),arm*PI/180);
	armVec = q.toRotate(armVec);

	return 0;
}

int Robot::sensorUpdate()
{
	sensor.set(l,dF,dU);
	return 0;
}

//////////////////////////////////////////////////////////////////
int Robot::run(double time)
{
	ctrl.step(time);

	setv(dF.nor() * speed);
	DirParticle::run(time);
	armUpdate();
	sensorUpdate();
	if (carrying != NULL)
	{
		carrying->set(l+armVec,dF,dU);
		carrying->beingcarried = 1;
	}

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

int Robot::tocarry(Box *b)
{
	carrying = b;
	b->set(l+armVec,dF,dU);
	b->beingcarried = 1;
	return 0;
}

int Robot::tounload(
				double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r)
{
	if (carrying != NULL)
	{
		Quaternion qua;
		qua.setFrom4Vecs(Vector3(1,0,0),Vector3(0,0,1),
						dF,dU	);

		Vector3 _l = l + qua.toRotate(Vector3(x,y,z));
		Vector3 _dF = qua.toRotate(Vector3(a,b,c));
		Vector3 _dU = qua.toRotate(Vector3(p,q,r));
		carrying->set(_l, _dF, _dU);
		carrying->beingcarried = 0;
		carrying->fixed = 1;
	}
	carrying = NULL;

	return 0;
}
