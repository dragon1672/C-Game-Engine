#pragma once

#include <luacppinterface.h>
#include <Engine/Tools/MasterLua.h>


//------------------------------------------Notes------------------------------------------
// These functions are made to make it easier to bind complex objects in LUA
// ASSUMES THAT: operator LuaUserdata<type> has been created for each object
// all conversions happen by casting
//
// THAT MEANS
// you should use the function generators at a class level
// you should use the binding defines in operator LuaUserdata<type> function
//-----------------------------------------------------------------------------------------





//----------------core tools-----------------
// Used to make hacks and string magic work
//-------------------------------------------
//makes pram a string returning "x"
#define LUA_STRING(x) #x
#define LUA_GLEW(a,b) LUA_STRING(a##b)





//This creates a LuaUserData for your class
//it overrides the default destructor that calls delete since we are pointing to "this"
#define MAKE_LUA_INSTANCE_RET(class_name,Userdata_var_name)\
	LuaUserdata<class_name> Userdata_var_name = LUA_INSTANCE.CreateUserdata<class_name>((##class_name##*)this,[](class_name*){}) // have to kill the destructor otherwise it calls delete on instance



//---------------------------overloading functions with lua counterparts---------------------------
// the following defines create functions that cast LuaUserdata version of variables and functions
// example:
// creates LuaUserdata<varType> get_lua_myAwesomeVar() { [casting magic] }
//-------------------------------------------------------------------------------------------------

//creates a getX() and setX(float)
#define LUA_VECTOR_MAKE_GETTER_SETTER(Uppercase,LowerCase)\
	inline float get##Uppercase##() { return LowerCase; }                 \
	inline void  set##Uppercase##(float LowerCase) { this->LowerCase = LowerCase; }

//creates LuaUserData function for pointer
//it will de-ref and cast as LuaUserdata
#define GET_LUA_VER_PTR(var_type,real_var) LuaUserdata<var_type>get_lua_##real_var##() { return (LuaUserdata<var_type>)(*real_var); }
//casts and returns LuaUserdata version
#define GET_LUA_VER(var_type,real_var) LuaUserdata<var_type>get_lua_##real_var##() { return (LuaUserdata<var_type>)real_var; }

//calls function de-refs and casts as LuaUserdata
#define LUA_GET_FUN_PTR(var_type,fun_name) LuaUserdata<##var_type##> fun_name##_LUA() { return (LuaUserdata<##var_type##>)*##fun_name##(); }




//---------------------------Bind overloaded functions into lua---------------------------
// the following defines bind into lua using original variable names
// example:
// creates bind("myAwesomeVar",get_lua_myAwesomeVar)
// call in lua: myAwesomeVar()
//----------------------------------------------------------------------------------------


//binds get_lua_var into lua
#define BIND_LUA_VER(class_name,Userdata_var_name,real_var) Userdata_var_name.Bind(#real_var,  &##class_name##::get_lua_##real_var  )

//binds getX and setX in LUA
#define LUA_VECTOR_BIND(vec_type,Userdata_var_name,UppercaseLetter)\
	Userdata_var_name.Bind(LUA_GLEW(set,UppercaseLetter),&##vec_type##::set##UppercaseLetter##);\
	Userdata_var_name.Bind(LUA_GLEW(get,UppercaseLetter),&##vec_type##::get##UppercaseLetter##)
//binds function 
#define LUA_BIND_FUN(class_name,Userdata_var_name,fun_name) Userdata_var_name.Bind(#fun_name,&##class_name##::##fun_name##_LUA)