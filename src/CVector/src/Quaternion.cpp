#include "Quaternion.h"
#include <stdio.h>	// for sprintf in toStr, and printf
#include <math.h>	// for sqrt

Quaternion::Quaternion()
	{ set(0,0,0,0); }
Quaternion::Quaternion(double _x, double _y, double _z, double _w)
	{ set(_x,_y,_z,_w); }
Quaternion::Quaternion(const Vector3& _l, double _w)
	{ set(_l,_w); }
Quaternion::Quaternion(const Quaternion& _x)
	{ set(_x); }

Quaternion::~Quaternion()
{
	//printf("i am a destroyer\n");
}

int Quaternion::set(double _x, double _y, double _z, double _w)
{
	l.set(_x,_y,_z);
	w = _w;
	return 0;
}

int Quaternion::set(const Vector3& _l, double _w)
{
	l.set(_l);
	w = _w;
	return 0;
}

int Quaternion::set(const Quaternion& _x)
{
	l = _x.l;
	w = _x.w;
	return 0;
}

Quaternion& Quaternion::setFromRotation(const Vector3& _l, double _w)
{
	double halfth = _w/2;
	l = _l.nor() * sin(halfth);
	w = cos(halfth);
	return *this;
}

char* Quaternion::toStr()
{
	sprintf(strForMe, "(%s, %lf)",l.toStr(),w);
	return strForMe;
}

////////  operator  + - * / ///////////////////

Quaternion& Quaternion::operator+=(const Quaternion& _x)
{
	l += _x.l;
	w += _x.w;
	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& _x)
{
	l -= _x.l;
	w -= _x.w;
	return *this;
}

Quaternion  Quaternion::operator-()
{
	Quaternion c(0,0,0,0);
	c -= *this;
	return c;
}

Quaternion  Quaternion::operator-(const Quaternion& _x)
{
	Quaternion c(*this);
	c -= _x;
	return c;
}

Quaternion  Quaternion::operator+(const Quaternion& _x)
{
	Quaternion c(*this);
	c += _x;
	return c;
}

Quaternion& Quaternion::operator*=(double _x)
{
	l *= _x;
	w *= _x;
	return *this;
}
Quaternion& Quaternion::operator/=(double _x)
{
	if (_x == 0)
	{
		printf("in Quaternion, /=, tried to divided by 0\n");
		this->set(0,0,0,0);
		return *this;
	}

	l /= _x;
	w /= _x;
	return *this;
}

Quaternion Quaternion::operator*(double _x)
{
	return Quaternion(l*_x, w*_x);
}

Quaternion Quaternion::operator/(double _x)
{
	if (_x == 0)
	{
		printf("in Quaternion, /, tried to divided by 0\n");
		return Quaternion(0,0,0,0);
	}
	return Quaternion(l/_x, w/_x);
}

Quaternion Quaternion::operator*(const Quaternion& _x)
{
	Quaternion c((this->l * _x.l) + (this->w * _x.l) + (this->l * _x.w),
				 (this->w * _x.w) - (this->l ^ _x.l));
	return c;
}

//////////  len and inv  //////////////////
double Quaternion::len()
{
	return sqrt(l.x * l.x + l.y * l.y + l.z * l.z +
				w * w);
}

Quaternion Quaternion::inv()
{
	double ll = len();
	if (ll == 0)
	{
		printf("in Quaternion, inv(), len == 0\n");
		return Quaternion(0,0,0,0);
	}

	return Quaternion(-l/ll,w/ll);
}

//////////// rotation ///////////////////
Vector3 Quaternion::toRotate(const Vector3& _x)
{
	/*
	if ((l.len() == 0) && (_x == 0))
		return _x;
		*/

	Quaternion p(_x,0);
	Quaternion res = (*this) * p;
	res = res * (this->inv());
	return res.l;
}
