#include <stdio.h>
#include <string.h>
extern "C"
{
#include <lauxlib.h>
#include <lualib.h>
#include <lua.h>
}
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
	int n = luaL_checkinteger(L,1);
	int size = n * sizeof(Student);
	struct Student *p = (struct Student *)lua_newuserdata(L,size);
	return 1;
}
//
static int SetName(lua_State *L)
{
	struct Student * p_st = (struct Student*)lua_touserdata(L,1);
	std::string name = luaL_checkstring(L,2);
	int id = luaL_checkinteger(L,3);
	(p_st + id - 1)->name = name;
	std::cout<<name<<std::endl;
	return 0;
}
static int GetName(lua_State *L)
{
        struct Student * p_st = (struct Student*)lua_touserdata(L,1);
        std::string name;
        int id = luaL_checkinteger(L,2);
	name = (p_st + id - 1)->name;
	std::cout<<name<<std::endl;
	lua_pushstring(L,name.c_str());
	return 1;
}

const char * test = "tmp = new(2); setname(tmp,2\"xiaoming\"); print(getname(tmp,2));";
int main()
{
	static lua_State * L;
	L = luaL_newstate();
	std::cout<<"LINE:"<<__LINE__<<std::endl;
	luaL_openlibs(L);
	std::cout<<"LINE:"<<__LINE__<<std::endl;
	lua_register(L,"new",NewStudents);
	std::cout<<"LINE:"<<__LINE__<<std::endl;
	lua_register(L,"setname",SetName);
	std::cout<<"LINE:"<<__LINE__<<std::endl;
	lua_register(L,"getname",GetName);
	std::cout<<"LINE:"<<__LINE__<<std::endl;
	luaL_dostring(L,test);
	std::cout<<"LINE:"<<__LINE__<<std::endl;
	lua_close(L);
	return 0;
}
















