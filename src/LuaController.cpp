#include <stdio.h>
#include "LuaController.h"
#include "Robot.h"

int setspeed(lua_State* L)
{
	Robot* robot = (Robot*)lua_touserdata(L,-2);
	double x = lua_tonumber(L,-1);
	printf("i clua setspeed %lf\n",x);
	robot->setspeed(x);
	return 0;
}

static const luaL_Reg clib[] = 
{
	{"setspeed",setspeed},
	//{"setturn",setturn},
	//{"setarm",setarm},
	{NULL,NULL},
};

int LuaController::init(int* r)
{
	robot = r;
	printf("i am init\n");
	L = luaL_newstate();
	luaL_openlibs(L);

	// table Robot = {setspeed ..}
	lua_newtable(L);
	luaL_setfuncs(L,clib,0);
	lua_setglobal(L,"Robot");
	// a metatable (without a name) of Robot
	luaL_newmetatable(L,"Robot");
	// mt.__index = Icey
	lua_pushstring(L,"__index");
	lua_getglobal(L,"Robot");
	lua_settable(L,-3);
	lua_pop(L,1);	// pop this metatable

	//Robot* ud = (Robot*)lua_newuserdata(L, sizeof(Robot));
	//ud = (Robot*)robot;
	//lua_pushvalue(L,-1);
	lua_pushlightuserdata(L,(void*)robot);
	luaL_getmetatable(L,"Robot");
	lua_setmetatable(L,-2);
	lua_setglobal(L,"robot");

	// load RobotCtrl.lua
	if ( (luaL_loadfile(L,"../src/RobotCtrl.lua")) || (lua_pcall(L,0,0,0)) )
		{printf("loadfile RobotCtrl.lua fail %s\n",lua_tostring(L,-1)); 
		return -1;}

	// call lua init
	//lua_settop(L,0);
	lua_getglobal(L,"init"); // stack 1 is the function
	if (lua_pcall(L,0,0,0) != 0)    // one para, one return
		{printf("call init func fail %s\n",lua_tostring(L,-1)); return -1;}

	return 0;
}
int LuaController::step()
{
	printf("i am step\n");
	// call lua step
	//lua_settop(L,0);
	lua_getglobal(L,"step"); // stack 1 is the function
	if (lua_pcall(L,0,0,0) != 0)    // one para, one return
		{printf("call step func fail %s\n",lua_tostring(L,-1)); return -1;}
	return 0;
}
int LuaController::exit()
{
	printf("i am exit\n");
	// call lua exit
	//lua_settop(L,0);
	lua_getglobal(L,"destroy"); // stack 1 is the function
	if (lua_pcall(L,0,0,0) != 0)    // one para, one return
		{printf("call exit func fail %s\n",lua_tostring(L,-1)); return -1;}
	return 0;
}
