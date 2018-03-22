#ifndef ROBOT
#define ROBOT

#include "DirParticle.h"
#include "LuaController.h"
#include "Sensor.h"

class Robot	: public DirParticle
{
public:
	//double speed = 0;	// the speed toward front(dirFront or dF)
	double speed;	// the speed toward front(dirFront or dF)
	//double arm = 0;		// in degree
	double arm;		// in degree
	Vector3 armVec;
	//double size = 0.1;
	double size;
	//double armLen = size;
	double armLen;
	int armUpdate();	// also update sensor

	RobotController ctrl;
	int ctrlInit();	
		// in main may have to call this in main,(like a.ctrlInit) after construct
		// otherwise it is the constructor it pushed in lua

	Sensor sensor;
	int sensorUpdate();

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

	int set(	double x,double y,double z);
	int set(	double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r);
	int set(	const Vector3& _x);
	int set(	const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z);

	int run(double time);
	int setspeed(double x);
	int setturn(double x);	// in degree
	int setarm(double x);	// in degree  0-90
};

#endif
