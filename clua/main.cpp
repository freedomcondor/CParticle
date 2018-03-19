#include <stdio.h>
#include <lua.hpp>
#include "icey.cpp"

static const luaL_Reg clib[] = 
{
	{"cry",cry},
	{NULL,NULL},
};

int main()
{
	Icey icey;
	printf("in C\n");
	icey.cry();
	icey.cry();
	icey.cry();
	icey.cry();
	icey.cry();
	icey.cry();

	printf("try lua\n");
	lua_State *L;
	L = luaL_newstate();
	luaL_openlibs(L);

	// a global variable
	lua_newtable(L);
	lua_pushstring(L,"value");
	lua_pushstring(L,"i am a value");
	lua_setglobal(L,"globalstr");

	// a table Icey = {angry = function ()xx}
	lua_newtable(L);
	luaL_setfuncs(L,clib,0);
	lua_setglobal(L,"Icey");
	// a metatable (without a name) of Icey
	luaL_newmetatable(L,"Icey");
	// mt.__index = Icey
	lua_pushstring(L,"__index");
	lua_getglobal(L,"Icey");
	lua_settable(L,-3);
	lua_pop(L,1);	// pop this metatable

	//Icey* ud = (Icey*)lua_newuserdata(L, sizeof(Icey));
	//*ud = icey;
	//lua_pushvalue(L,-1);
	lua_pushlightuserdata(L,(void*)&icey);
	luaL_getmetatable(L,"Icey");
	lua_setmetatable(L,-2);
	lua_setglobal(L,"icey");

	if ( (luaL_loadfile(L,"iceyctl.lua")) || (lua_pcall(L,0,0,0)) )
		{printf("call exit func fail %s\n",lua_tostring(L,-1)); return -1;}

	//lua function init()
	lua_settop(L,0);
	lua_getglobal(L,"init"); // stack 1 is the function
	if (lua_pcall(L,0,0,0) != 0)    // one para, one return
		{printf("call init func fail %s\n",lua_tostring(L,-1)); return -1;}

	for (int i = 0; i < 3; i++)
	{
		lua_settop(L,0);
		lua_getglobal(L,"step"); // stack 1 is the function
		if (lua_pcall(L,0,0,0) != 0)    // one para, one return
			{	printf("call step func fail %s\n",lua_tostring(L,-1)); 
				return -1;}
	}

	return 0;
}
