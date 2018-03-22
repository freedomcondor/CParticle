#ifndef QUATERNION
#define QUATERNION

#include "Vector3.h"

class Quaternion
{
public:
	Vector3 l;
	double w;
	Quaternion();
	Quaternion(double _x, double _y, double _z, double _w);
	Quaternion(const Vector3& _l, double _w);
	Quaternion(const Quaternion& _x);
	~Quaternion();

	int set(double _x, double _y, double _z, double _w);
	int set(const Vector3& _l, double _w);
	int set(const Quaternion& _x);
	Quaternion& setFromRotation(const Vector3& _l, double _w);
	Quaternion& setFrom4Vecs(const Vector3& _abc_o,const Vector3& _pqr_o,
							 const Vector3& _abc,  const Vector3& _pqr);

	// operators
	Quaternion& operator+=(const Quaternion& _x);
	Quaternion& operator-=(const Quaternion& _x);
	Quaternion  operator-();
	Quaternion  operator-(const Quaternion& _x);
	Quaternion  operator+(const Quaternion& _x);
	Quaternion  operator*(double _x);
	Quaternion  operator/(double _x);
	Quaternion& operator*=(double _x);
	Quaternion& operator/=(double _x);

	Quaternion operator*(const Quaternion& _x);

	// len & inv
	double len();
	Quaternion inv();

	// rotate
	Vector3 toRotate(const Vector3& _x);

public:
	char* toStr();
private:
	char strForMe[100];
};

#endif
