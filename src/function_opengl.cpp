#include<math.h>
#include<stdio.h>	// for printf
#include<time.h>  // for time measuring

#include"function_opengl.h"
//#include "Particle.h"
#include "DirParticle.h"
#include"Robot.h"
#include"Sensor.h"
#include"CVector/Vector3.h"

//#include<lua.hpp>

#define pi 3.1415926
#define ZERO 0.0000001

#define Max_plot 10000

/////////////////// control communications /////////////////
double CH1 = 0,CH1_MAX = 30,CH1_MIN = -30,CH1_STEP = 0.05;
double CH2 = 0,CH2_MAX = 30,CH2_MIN = -30,CH2_STEP = 0.01;

///////////////////  function definations /////////////////
//
//

double buffer_draw2 = 0;
double plot_y_max = 0;
double plot_x_max = 0;
double datalog[Max_plot];

///////////////////  functions  ///////////////////////////
int function_exit()
{

	return 0;
}

//DirParticle a(0,0,0);
//DirParticle a(0,0,0,
Robot a;
Signal b;
Sensor c;

int function_init()
{
	printf("i am init of main\n");
	a = Robot(0,0,0,
				0,1,0,
				0,0,1);
	a.ctrlInit();

	b = Signal(0.1,0,0,
				0,1,0,
				0,0,1);

	c = Sensor(-0.1,0,0,
				0,1,0,
				0,0,1);
	
	b.copy(a);
	c.sense(a);

	return 0;
}

int function_step(double time)	// time in ms
{
	//a.setspeed(CH2);
	//a.setarm(CH2 * 180 / 3.1415926535898);
	a.setturn(CH1 * 180 / 3.1415926535898);
	a.run(time/1000);
	//clock_t start_t, end_t;
	//start_t = clock();
	//end_t = clock();
	//printf("step time: %lf\n",double(end_t - start_t)*1000/CLOCKS_PER_SEC);
	return 0;
}

////////////////////////// draw ///////////////////
int drawRobot(const Robot& r);
int function_draw()
{
	/*
	drawSphere(a.l.x, a.l.y, a.l.z, 0.02);
	drawCylinder(	0.01,0.01,0.05,
					a.l.x, a.l.y, a.l.z,
					a.dF.x, a.dF.y, a.dF.z );
	drawCylinder(	0.01,0.01,0.05,
					a.l.x, a.l.y, a.l.z,
					a.dU.x, a.dU.y, a.dU.z );
	*/
	drawRobot(a);

	return 0;
}

int function_draw2()
{
	/*
	for (int i = 1; i <= herd.time; i++)
	{
		if (herd.time < plot_x_max)
		{
		glBegin(GL_LINES);
			glVertex3f( (i-1)/plot_x_max,	datalog[i-1]/plot_y_max,0.0f);
			glVertex3f(  i/plot_x_max,		datalog[i] / plot_y_max,0.0f);
		glEnd();
		}
		else
		{
		glBegin(GL_LINES);
			glVertex3f( 1.0*(i-1)/herd.time,	datalog[i-1]/plot_y_max,0.0f);
			glVertex3f( 1.0* i/herd.time,		datalog[i] / plot_y_max,0.0f);
		glEnd();
		}
	}
	*/
		
	return 0;
}

int drawRobot(const Robot& r)
{
	drawCube(r.size/2, 	r.l.x,  r.l.y,  r.l.z,
			 			r.dF.x, r.dF.y, r.dF.z,
			 			r.dU.x, r.dU.y, r.dU.z);

	drawCylinder(r.size/8, r.size/8, r.size/2,
			 			r.l.x, r.l.y, r.l.z,
			 			r.armVec.x, r.armVec.y, r.armVec.z);
	return 0;
}


////////////////////////////// drawings  /////////////////////////
int drawSphere(double x, double y, double z, double r)
{
	glTranslatef(x,y,z);
	glutSolidSphere(r,10,10);
	glTranslatef(-x,-y,-z);

	return 0;
}

int drawCube(double half, double x, double y, double z, 
						  double fx,double fy,double fz,
						  double ux,double uy,double uz)
	// f is front, u is up
{
	double xaxis,yaxis,zaxis,axis,angleaxis;
	double fxbase,fybase,fzbase;
	double uxbase,uybase,uzbase;
	double fe,ue;
	double fxdiff,fydiff,fzdiff;
	double uxdiff,uydiff,uzdiff;
	double rf,xrf, yrf, zrf;  // rotation from
	double rt,xrt, yrt, zrt;  // rotation to
	double temp;
	double cos;

	int rotateflag = 1;

	if (((fx-0)*(fx-0)<ZERO) && ((fy-0)*(fy-0)<ZERO) && ((fz-0)*(fz-0)<ZERO))
		rotateflag = 0;
	if (((ux-0)*(ux-0)<ZERO) && ((uy-0)*(uy-0)<ZERO) && ((uz-0)*(uz-0)<ZERO))
		rotateflag = 0;
	if ((fx == 1) && (fy == 0) && (fz == 0))
	{
		drawCube(half, x,y,z,  ux,uy,uz,  fx,fy,fz);
		return 0;
	}

	//  some problem for specific situation
	// 		only general case and
	// 		only work for right angle and u = 0,0,1
	if (rotateflag == 1)
	{
		fe = sqrt(fx * fx + fy * fy + fz * fz);
		if (fe == 0) return -1;
		ue = sqrt(ux * ux + uy * uy + uz * uz);
		if (ue == 0) return -1;
		fx /= fe; fy /= fe; fz /= fe;
		ux /= ue; uy /= ue; uz /= ue;

		// fbase = (1,0,0), ubase = (0,0,1)
		fxbase = 1; fybase = 0; fzbase = 0;
		uxbase = 0; uybase = 0; uzbase = 1;

		//  fdiff = f - fbase,  udiff = u - ubase
		fxdiff=fx-fxbase; fydiff=fy-fybase; fzdiff=fz-fzbase;
		uxdiff=ux-uxbase; uydiff=uy-uybase; uzdiff=uz-uzbase;

		// xaxis = fdiff * udiff
		xaxis = fydiff * uzdiff - uzdiff * fydiff;
		yaxis = fzdiff * uxdiff - uxdiff * fzdiff;
		zaxis = fxdiff * uydiff - uydiff * fxdiff;

		axis = sqrt(xaxis * xaxis + yaxis * yaxis + zaxis * zaxis);
		if (!(axis*axis < ZERO))
			{xaxis /= axis; yaxis /= axis; zaxis /= axis;}

		// rot_from = base - axis .* f * axis
		temp = xaxis * fx + yaxis * fy + zaxis * fz;
		xrf = fxbase - temp * xaxis;
		yrf = fybase - temp * yaxis;
		zrf = fzbase - temp * zaxis;
		xrt = fx - temp * xaxis;
		yrt = fy - temp * yaxis;
		zrt = fz - temp * zaxis;
		rf = sqrt(xrf*xrf + yrf*yrf + zrf*zrf);
		if (!(rf*rf < ZERO))
			{xrf /= rf; yrf /= rf; zrf /= rf;}
		rt = sqrt(xrt*xrt + yrt*yrt + zrt*zrt);
		if (!(rt*rt < ZERO))
			{xrt /= rt; yrt /= rt; zrt /= rt;}

		cos = xrf * xrt + yrf * yrt + zrf * zrt;
		angleaxis = acos(cos);
		xaxis = yrf * zrt - zrf * yrt;
		yaxis = zrf * xrt - xrf * zrt;
		zaxis = xrf * yrt - yrf * xrt;

		//angleaxis = acos((xbase*ex+ybase*ey+zbase*ez)/e) + pi;
		//printf("%lf %lf %lf %lf\n",angleaxis,xaxis,yaxis,zaxis);
	}

	///*
	glTranslatef(x,y,z);
	if (rotateflag == 1)
		glRotatef(angleaxis*180/pi,xaxis,yaxis,zaxis);
	glutSolidCube(half);
	if (rotateflag == 1)
		glRotatef(-angleaxis*180/pi,xaxis,yaxis,zaxis);
	glTranslatef(-x,-y,-z);
	//*/

	return 0;
}

int drawCylinder(	double base, double top, double height,
				double lx,	double ly, double lz,
				double ex,	double ey, double ez
			)
{
	double xaxis,yaxis,zaxis,angleaxis;
	double xbase,ybase,zbase;
	double e;
	int rotateflag = 1;
	GLUquadricObj *quadratic;

	quadratic = gluNewQuadric();

	//printf("l: %lf %lf %lf\n",lx,ly,lz);
	//printf("e: %lf %lf %lf\n",ex,ey,ez);

	if (((ex-0)*(ex-0)<ZERO) && ((ey-0)*(ey-0)<ZERO) && ((ez-1)*(ez-1)<ZERO))
		rotateflag = 0;

	if (rotateflag == 1)
	{
		e = sqrt(ex * ex + ey * ey + ez * ez);
		if (e == 0) return -1;

		xbase = 0; ybase = 0; zbase = 1;
		xaxis = ybase * ez - zbase * ey;
		yaxis = zbase * ex - xbase * ez;
		zaxis = xbase * ey - ybase * ex;
		//angleaxis = acos((xbase*ex+ybase*ey+zbase*ez)/e) + pi;
		angleaxis = acos((xbase*ex+ybase*ey+zbase*ez)/e);

		//printf("%lf %lf %lf %lf\n",angleaxis,xaxis,yaxis,zaxis);

	}
	if (((ex-0)*(ex-0)<ZERO) && ((ey-0)*(ey-0)<ZERO) && ((ez+1)*(ez+1)<ZERO))
	{
		xaxis = 1; yaxis = 0; zaxis = 0;
		angleaxis = pi;
	}

	glTranslatef(lx,ly,lz);

	if (rotateflag == 1)
		glRotatef(angleaxis*180/pi,xaxis,yaxis,zaxis);

	gluCylinder(quadratic,base,top,height,32,32);//»­Ô²Öù	base top height
	if (rotateflag == 1)
		glRotatef(-angleaxis*180/pi,xaxis,yaxis,zaxis);

	glTranslatef(-lx,-ly,-lz);
	return 0;
}
