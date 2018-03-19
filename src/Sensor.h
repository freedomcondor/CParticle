#ifndef SENSOR
#define SENSOR

#include "DirParticle.h"
#include "Robot.h"

#define MAXSENSE 50
#define sigRobot 0
#define sigBox 1

class Signal : public DirParticle
{
public:
	int type;
	const Robot* obj;
	//Box* obj;
	int copy(const Robot& x);
	//int copy(const Box& x);
	int copyDirP(const DirParticle& x);

	Signal();
	Signal(double x,double y,double z);
	Signal(	double x,double y,double z,
			double a,double b,double c,
			double p,double q,double r);
		// x,y,z location,  a,b,c: front, p,q,r, up

	Signal(const Vector3& _x);
	Signal(	const Vector3& _x,
			const Vector3& _y,
			const Vector3& _z);
	//Particle(const Particle& _x);
	~Signal();
	int commonInit();
};

class Sensor : public DirParticle
{
public:
	int n;
	Signal sig[MAXSENSE];

	Sensor();
	Sensor(double x,double y,double z);
	Sensor(	double x,double y,double z,
			double a,double b,double c,
			double p,double q,double r);
		// x,y,z location,  a,b,c: front, p,q,r, up

	Sensor(const Vector3& _x);
	Sensor(	const Vector3& _x,
			const Vector3& _y,
			const Vector3& _z);
	//Particle(const Particle& _x);
	~Sensor();
	int commonInit();

	int sense(const Robot& x);
	int sensecheck(const Signal& x);
	int addsig(const Signal& x);
	//int sense(const Box& x);
};

#endif
