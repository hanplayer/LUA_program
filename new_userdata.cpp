#include <stdio.h>
#include <string.h>
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
#include <string>
#include <iostream>

struct Student
{
public:
	std::string name;
	int ID;
	int age;
	std::string sex;
	
	
};
//
static int NewStudents(lua_State *L)
{
	int n = luaL_checkint(L,1);
	int size = n * sizeof(Student);
	struct Student *p = (struct Student *)lua_newuserdata(L,size);
	return 1;
}
//
static int SetName(lua_State *L)
{
	struct Student * p_st = (struct Student*)lua_touserdata(L,1);
	std::string name = luaL_checkstring(L,2);
	int id = luaL_checkint(L,3);
	(p_st + id - 1)->name = name;
	return 0;
}
static int GetName(lua_State *L)
{
        struct Student * p_st = (struct Student*)lua_touserdata(L,1);
        std::string name;
        int id = luaL_checkint(L,2);
	name = (p_st + id - 1)->name;
	lua_pushstring(L,name);
	return 1;
}

const char * test = "tmp = new(2); tmp."
int main()
{
	lua_State * L;
	luaL_openlib(L);
	lua_register(L,"new",NewStudents);
	lua_register(L,"setname",SetName);
	lua_register(L,"getname",GetName);
	
	
	lua_close(L);
	return 0;
}
















