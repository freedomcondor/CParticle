#ifndef LUACONTROLLER
#define LUACONTROLLER

#include <lua.hpp>

class LuaController
{
public:
	LuaController();
	lua_State *L;
	int* robot;

	int init(int *r);
	int step();
	int exit();
};

#endif
