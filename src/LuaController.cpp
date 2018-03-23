#include <stdio.h>
#include "LuaController.h"
#include "Robot.h"
#include "Box.h"

int setspeed(lua_State* L)
{
	Robot* robot = (Robot*)lua_touserdata(L,-2);
	double x = lua_tonumber(L,-1);
	robot->setspeed(x);
	return 0;
}
int setturn(lua_State* L)
{
	Robot* robot = (Robot*)lua_touserdata(L,-2);
	double x = lua_tonumber(L,-1);
	robot->setturn(x);
	return 0;
}
int setarm(lua_State* L)
{
	Robot* robot = (Robot*)lua_touserdata(L,-2);
	double x = lua_tonumber(L,-1);
	robot->setarm(x);
	return 0;
}

static const luaL_Reg clib_robot[] = 
{
	{"setspeed",setspeed},
	{"setturn",setturn},
	{"setarm",setarm},
	{NULL,NULL},
};

//////////////////////////////////////////////////////////////////////////////////
RobotController::RobotController()
{
	robot = NULL;
	selfsensor = NULL;

	L = luaL_newstate();
	luaL_openlibs(L);

	// table Robot = {setspeed ..}
	lua_newtable(L);
	luaL_setfuncs(L,clib_robot,0);
	lua_setglobal(L,"Robot");
	// a metatable (without a name) of Robot
	luaL_newmetatable(L,"Robot");
	// mt.__index = Icey
	lua_pushstring(L,"__index");
	lua_getglobal(L,"Robot");
	lua_settable(L,-3);
	lua_pop(L,1);	// pop this metatable

	// load RobotCtrl.lua
	if ( (luaL_loadfile(L,"../src/RobotCtrl.lua")) || (lua_pcall(L,0,0,0)) )
		{printf("loadfile RobotCtrl.lua fail %s\n",lua_tostring(L,-1));}
}

int RobotController::init(int* r)
{
	robot = r;
	selfsensor = (int*)&(  ((Robot*)r)->sensor   );

	lua_pushlightuserdata(L,(void*)robot);
	luaL_getmetatable(L,"Robot");
	lua_setmetatable(L,-2);
	lua_setglobal(L,"robot");

	// call lua init
	lua_settop(L,0);
	lua_getglobal(L,"init"); // stack 1 is the function
	if (lua_pcall(L,0,0,0) != 0)    // one para, one return
		{printf("call init func fail %s\n",lua_tostring(L,-1)); return -1;}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////
int setboxspeed(lua_State* L)
{
	Box* box = (Box*)lua_touserdata(L,-2);
	double x = lua_tonumber(L,-1);
	box->setspeed(x);
	return 0;
}
static const luaL_Reg clib_box[] = 
{
	{"setspeed",setboxspeed},
	{NULL,NULL},
};

BoxController::BoxController()
{
	box = NULL;
	selfsensor = NULL;

	L = luaL_newstate();
	luaL_openlibs(L);

	// table Box = {setspeed ..}
	lua_newtable(L);
	luaL_setfuncs(L,clib_box,0);
	lua_setglobal(L,"Box");
	// a metatable (without a name) of Robot
	luaL_newmetatable(L,"Box");
	// mt.__index = Icey
	lua_pushstring(L,"__index");
	lua_getglobal(L,"Box");
	lua_settable(L,-3);
	lua_pop(L,1);	// pop this metatable

	// load RobotCtrl.lua
	if ( (luaL_loadfile(L,"../src/BoxCtrl.lua")) || (lua_pcall(L,0,0,0)) )
		{printf("loadfile BoxCtrl.lua fail %s\n",lua_tostring(L,-1));}
}

int BoxController::init(int* r)
{
	box = r;
	selfsensor = (int*)&(  ((Box*)r)->sensor   );

	lua_pushlightuserdata(L,(void*)box);
	luaL_getmetatable(L,"Box");
	lua_setmetatable(L,-2);
	lua_setglobal(L,"box");

	// call lua init
	lua_settop(L,0);
	lua_getglobal(L,"init"); // stack 1 is the function
	if (lua_pcall(L,0,0,0) != 0)    // one para, one return
		{printf("call init func fail %s\n",lua_tostring(L,-1)); return -1;}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////
int lua_pushSig(lua_State *L, Signal sig);
int LuaController::pushSensor()
{
	Sensor *s;
	s = (Sensor*)selfsensor;

	struct node *head, *p;

	lua_newtable(L);
		lua_pushstring(L,"n");
		lua_pushnumber(L,s->n);
		lua_settable(L,-3);

		head = s->siglist.head;
		p = head->next;
		for (int i = 1; i <= s->n; i++)
		{
			lua_pushnumber(L,i);
			lua_pushSig(L,p->obj);
			lua_settable(L,-3);
			p = p->next;
		}

	lua_setglobal(L,"sensor");
	return 0;
}

int lua_pushVec3(lua_State *L, Vector3 vec);
int lua_pushSig(lua_State *L, Signal sig)
{
	lua_newtable(L);
		lua_pushstring(L,"l");
		lua_pushVec3(L,sig.l);
	  lua_settable(L,-3);
		lua_pushstring(L,"dF");
		lua_pushVec3(L,sig.dF);
	  lua_settable(L,-3);
		lua_pushstring(L,"dU");
		lua_pushVec3(L,sig.dU);
	  lua_settable(L,-3);
	return 0;
}
int lua_pushVec3(lua_State *L, Vector3 vec)
{
	lua_newtable(L);
		lua_pushstring(L,"x");
		lua_pushnumber(L,vec.x);
	  lua_settable(L,-3);
		lua_pushstring(L,"y");
		lua_pushnumber(L,vec.y);
	  lua_settable(L,-3);
		lua_pushstring(L,"z");
		lua_pushnumber(L,vec.z);
	  lua_settable(L,-3);
	return 0;
}

/////////////////////////////////////////////////////////////
int LuaController::step(double time)
{
	lua_settop(L,0);
	pushSensor();

	lua_pushnumber(L,time);
	lua_setglobal(L,"steptime");

	// call lua step
	//printf("Controller step\n");
	lua_getglobal(L,"step"); // stack 1 is the function
	if (lua_pcall(L,0,0,0) != 0)    // one para, one return
		{printf("call step func fail %s\n",lua_tostring(L,-1)); return -1;}
	return 0;
}
int LuaController::exit()
{
	// call lua exit
	lua_settop(L,0);
	lua_getglobal(L,"destroy"); // stack 1 is the function
	if (lua_pcall(L,0,0,0) != 0)    // one para, one return
		{printf("call exit func fail %s\n",lua_tostring(L,-1)); return -1;}
	return 0;
}
