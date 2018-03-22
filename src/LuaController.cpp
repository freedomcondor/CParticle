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
int LuaController::step()
{
	// call lua step
	//printf("Controller step\n");
	lua_settop(L,0);
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
