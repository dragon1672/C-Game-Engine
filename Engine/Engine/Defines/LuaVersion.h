#pragma once

#include <luacppinterface.h>
#include <Engine/Tools/MasterLua.h>

//this disables the destructor call
#define MAKE_LUA_INSTANCE_RET(class_name,varname) LuaUserdata<class_name> varname = LUA_INSTANCE.CreateUserdata<class_name>((##class_name##*)this,[](class_name*){})

#define LUA_VECTOR_MAKE_GETTER_SETTER(Uppercase,LowerCase)\
	inline float get##Uppercase##() { return LowerCase; }                 \
	inline void  set##Uppercase##(float LowerCase) { this->LowerCase = LowerCase; }
#define LUA_STRING(x) #x
#define LUA_GLEW(a,b) LUA_STRING(a##b)
#define LUA_VECTOR_BIND(vec_type,Userdata_var_name,UppercaseLetter)\
	Userdata_var_name.Bind(LUA_GLEW(set,UppercaseLetter),&##vec_type##::set##UppercaseLetter##);\
	Userdata_var_name.Bind(LUA_GLEW(get,UppercaseLetter),&##vec_type##::get##UppercaseLetter##)


#define GET_LUA_VER_PTR(var_type,real_var) LuaUserdata<var_type>get_lua_##real_var##() { return (LuaUserdata<var_type>)(*real_var); }
#define GET_LUA_VER(var_type,real_var) LuaUserdata<var_type>get_lua_##real_var##() { return (LuaUserdata<var_type>)real_var; }
#define BIND_LUA_VER(class_name,Userdata_var_name,real_var) Userdata_var_name.Bind(#real_var,  &##class_name##::get_lua_##real_var  )

#define LUA_GET_FUN_PTR(var_type,fun_name) LuaUserdata<##var_type##> fun_name##_LUA() { return *((LuaUserdata<##var_type##>*)##fun_name##()); }

#define LUA_BIND_FUN(class_name,Userdata_var_name,fun_name) Userdata_var_name.Bind(#fun_name,&##class_name##::##fun_name##_LUA)