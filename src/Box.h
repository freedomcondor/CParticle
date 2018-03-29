#ifndef BOX
#define BOX

#include "DirParticle.h"
#include "LuaController.h"
#include "Sensor.h"

#define FRONT 0
#define LEFT 1
#define UP 2
#define DOWN 3
#define RIGHT 4
#define BACK 5

class Box	: public DirParticle
{
public:
	double size;
	int beingcarried;
	int fixed;
	int stign;
	int stig[6];

	Vector3 getStigVector(int x) const;	//x is FRONT/BACK/...

	BoxController ctrl;
	int ctrlInit();	
		// in have to call this in main,(like a.ctrlInit) after construct
		// otherwise it is the constructor it pushed in lua
	
	Sensor sensor;
	int sensorUpdate();

	//----------------------------------------------------
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

	//----------------------------------------------------
	int set(	double x,double y,double z);
	int set(	double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r);
	int set(	const Vector3& _x);
	int set(	const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z);

	//----------------------------------------------------
	int run(double time);
	int setstig(int x);
	int unsetstig(int x);
};

#endif
