#ifndef DIRPARTICLE
#define DIRPARTICLE

#include "CVector/Vector3.h"
#include "CVector/Quaternion.h"
#include "Particle.h"

class DirParticle : public Particle
{
public:
	// in father, Vector3 l,v,a
	Vector3 dF,dU;	// dirFront, dirUp	not necessary a nor
	Vector3 w,wa;	
		// rotation speed, rotation acc, right hand, len is speed in rad

	DirParticle();
	DirParticle(double x,double y,double z);
	DirParticle(double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r);
		// x,y,z location,  a,b,c: front, p,q,r, up

	DirParticle(const Vector3& _x);
	DirParticle(const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z);
	//Particle(const Particle& _x);
	~DirParticle();

	int set(	double x,double y,double z);
	int set(	double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r);
	int set(	const Vector3& _x);
	int set(	const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z);

	int setdF(double x,double y,double z);
	int setdF(const Vector3& _x);
	int setdU(double x,double y,double z);
	int setdU(const Vector3& _x);
	int setw(double x,double y,double z);
	int setw(const Vector3& _x);
	int setwa(double x,double y,double z);
	int setwa(const Vector3& _x);

	int run(double time);
};

#endif
