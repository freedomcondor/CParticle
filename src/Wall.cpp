#include "Wall.h"

int Wall::makesignal(
	const Vector3& _l,const Vector3& _dF,const Vector3& _dU,
	Vector3 *l, Vector3 *dF, Vector3 *dU, double *dis) const
{
	double range = 1.5;

	*l = Vector3(_l.x,_l.y,0).nor() * range;
	if ((_l.x == 0) && (_l.y == 0))
		*l = Vector3(range,0,0);
	l->z = _l.z;
	
	*dF = Vector3(1,0,0);
	*dU = Vector3(0,0,1);

	*dis = range - Vector3(_l.x,_l.y,0).len();

	return 0;
}
