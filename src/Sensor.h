#ifndef SENSOR
#define SENSOR

#include "CVector/Vector3.h"
#include "Robot.h"
#include "Box.h"

#define MAXSENSE 50
#define SIGROBOT 0
#define SIGBOX 1

#include "List/List.h"

class Sensor : public DirParticle
{
public:
	int n;
	List siglist;

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
	int sense(const Box& x);
	int addSig(const Signal& s);
	bool rangecheck(const Signal& x);
	//int sense(const Box& x);
};
#endif
