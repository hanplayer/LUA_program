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
	char  name[30];
	int ID;
	int age;
	char sex[8];//male or female
	
	
};
//
static int NewStudents(lua_State *L)
{
	Student stu;
	sprintf(stu.name,"%s","heheda");
	int size = sizeof(struct Student);
	struct Student *p = (struct Student *)lua_newuserdata(L,size);
	memcpy(p,&stu,sizeof(Student));
	return 1;
}
//
static int SetName(lua_State *L)
{
	struct Student * p_st = (struct Student*)lua_touserdata(L,1);
	std::string name = luaL_checkstring(L,2);
	sprintf((*p_st).name,"%s",name.c_str());
	return 0;
}
static int GetName(lua_State *L)
{
        struct Student * p_st = (struct Student*)lua_touserdata(L,1);
        std::string name;
	name = p_st ->name;
	lua_pushstring(L,name.c_str());
	return 1;
}

const char * test = "tmp = newStu(); print(getName(tmp));";
//const char * test = "print(\"111111\");";
int main()
{
	static lua_State * L;
	L = luaL_newstate();
	luaL_openlibs(L);
	lua_register(L,"newStu",NewStudents);
	lua_register(L,"setName",SetName);
	lua_register(L,"getName",GetName);
	if(luaL_dostring(L,test))
	{
		std::cout<<"error:"<<lua_tostring(L,-1)<<std::endl;
	}
	lua_close(L);
	return 0;
}
















