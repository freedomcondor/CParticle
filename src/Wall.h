#ifndef WALL
#define WALL

#include "CVector/Vector3.h"

class Wall
{
public:
	int makesignal(const Vector3& _l,const Vector3& _dF,const Vector3& _dU,
					Vector3 *l, Vector3 *dF, Vector3 *dU, double *dis) const;
			// _l, _dF, _dU are the location of the robot/box
			// &l,&dF,&dU are the absolute(need turn later) coordinate on the wall
};

#endif
