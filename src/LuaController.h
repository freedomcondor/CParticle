#ifndef LUACONTROLLER
#define LUACONTROLLER

#include <lua.hpp>

class LuaController
{
public:
	//LuaController();
	lua_State *L;

	int *selfsensor;
	int pushSensor();

	int init(int *r);
	int step();
	int exit();
};

class RobotController : public LuaController
{
public:
	int* robot;
	RobotController();
	int init(int *r);
};

class BoxController : public LuaController
{
public:
	int* box;
	BoxController();
	int init(int *r);
};

#endif
