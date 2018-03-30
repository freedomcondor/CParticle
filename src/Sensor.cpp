#include "Sensor.h"
#include "Robot.h"	// for copy
#include "Box.h"
#include "Wall.h"

#define PI 3.1415926535898
#define DOUBLE_ERR 0.0000001

Sensor::Sensor() 
	:DirParticle()
{
	commonInit();
}
Sensor::Sensor(double x,double y,double z) 
	:DirParticle(x,y,z)
{
	commonInit();
}
Sensor::Sensor(const Vector3& _x)
	:DirParticle(_x)
{
	commonInit();
}

Sensor::Sensor(double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r)
	:DirParticle(x,y,z,a,b,c,p,q,r)
{
	commonInit();
}

Sensor::Sensor(const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z)
	:DirParticle(_x,_y,_z)
{
	commonInit();
}

//DirParticle(const DirParticle& _x);
Sensor::~Sensor()
{
	//printf("I am the destructor of Sensor\n");
}

//////////////////////////////////////////////////////////////////
Signal::Signal() 
{
	l = Vector3(0,0,0);
	dF = Vector3(1,0,0);
	dU = Vector3(0,0,1);
	commonInit();
}
Signal::Signal(double x,double y,double z) 
{
	Signal();
	l = Vector3(x,y,z);
	commonInit();
}
Signal::Signal(const Vector3& _x)
{
	Signal();
	l = Vector3(_x);
	commonInit();
}

Signal::Signal(double x,double y,double z,
				double a,double b,double c,
				double p,double q,double r)
{
	l = Vector3(x,y,z);
	dF = Vector3(a,b,c);
	dU = Vector3(p,q,r);
	commonInit();
}

Signal::Signal(const Vector3& _x,
				const Vector3& _y,
				const Vector3& _z)
{
	l = Vector3(_x);
	dF = Vector3(_y);
	dU = Vector3(_z);
	commonInit();
}

//DirParticle(const DirParticle& _x);
Signal::~Signal()
{
	//printf("I am the destructor of Signal\n");
}

//////////////////////////////////////////////////////////////////
int Sensor::commonInit()
{
	n = 0;
	return 0;
}
int Signal::commonInit()
{
	return 0;
}

//////  function  ////////////////////////////////////////////////////////////
///// Signal //////////////////////////////////////////////////

int Signal::copy(const Box& x)
{
	type = SIGBOX;
	obj = (int*)&x;
	l = x.l;
	dF = x.dF;
	dU = x.dU;
	return 0;
}
int Signal::copy(const Robot& x)
{
	type = SIGROBOT;
	obj = (int*)&x;
	l = x.l;
	dF = x.dF;
	dU = x.dU;
	return 0;
}

int Signal::copy(const Wall& x, const Vector3& _x,const Vector3& _y,const Vector3& _z)
	// _x,_y,_z is the location and direction of the sensor
{
	type = SIGWALL;
	obj = (int*)&x;
	x.makesignal(_x,_y,_z,&l,&dF,&dU,&distance);
	return 0;
}

int Signal::copy(const Robot& x, double len)
{
	copy(x);
	distance = len;
	return 0;
}
int Signal::copy(const Box& x, double len)
{
	copy(x);
	distance = len;
	return 0;
}
int Signal::turn(const Vector3& _x,const Vector3& _y,const Vector3& _z)
		// calculate relative location, respect to _x as l, _y as dF, _z as dU
{
	l = l - _x;
	distance = l.len();

	Quaternion q;
	q.setFrom4Vecs(	_y,_z,
					Vector3(1,0,0),Vector3(0,0,1));

	l = q.toRotate(l);
	dF = q.toRotate(dF);
	dU = q.toRotate(dU);

	return 0;
}

///// Sensor //////////////////////////////////////////////////
int Sensor::sense(const Box& x)
{
	Signal s;
	s.copy(x);
	s.turn(l,dF,dU);
	addSig(s);
	return 0;
}
int Sensor::sense(const Robot& x)
{
	Signal s;
	s.copy(x);
	s.turn(l,dF,dU);
	addSig(s);
	return 0;
}
int Sensor::sense(const Wall& x)
{
	Signal s;
	s.copy(x,l,dF,dU);
	s.turn(l,dF,dU);
	addSig(s);
	return 0;
}

int Sensor::addSig(const Signal& s)
{
	struct node *p,*head,*q;	// struct node is defined n List.h
	head = siglist.head;
	int flag = 0;

	// scan to check the same obj
	q = head;
	while (q->next != NULL)
	{
		if ( (q->next->obj).obj == s.obj  )	// check if it is the same obj
		{
			if ( 	!rangecheck(s) )
			{
				// delete
				p = q->next;
				q->next = q->next->next;
				delete(p);
				n--;
				return 0;
			}
			q->next->obj = s;
			return 0;
		}
		q = q->next;
	}

	// to insert
	if (	!rangecheck(s) )
		return 0;

	double len = s.l.len();
	q = head;
	while (q->next != NULL)
	{
		if ( (q->next->obj).distance < len  )	// if len <
			q = q->next;
		else
			break;
	}
	p = (struct node*)malloc(sizeof(struct node));
	p->obj = s;
	p->next = q->next;
	q->next = p;
	n++;
		
	return 0;
}

bool Sensor::rangecheck(const Signal& x)
{
	if (x.l.len() < 0.15)
	{
		if (  (x.type == SIGBOX) && ( ((Box*)(x.obj))->beingcarried == 1) )
			return false;
		return true;
	}
	else
		return false;
}
