#include "GlmWrap.h"
#include <Engine/DebugTools/DebugMemHeader.h>


namespace wrap {
	vec3& vec3::operator=(const glm::vec3& that)
	{
		set(that);
		LUA_OBJECT_END(vec3);
		return *this;
	}

	vec3& vec3::operator=(const vec3& that)
	{
		set(that);
		LUA_OBJECT_END(vec3);
		delete that.LUA_HOLDER_INSTANCE;
		*(const_cast<vec3::LUA_HOLDER**>(&that.LUA_HOLDER_INSTANCE)) = nullptr;
		return *this;
	}

	void vec3::set(const glm::vec3& that)
	{
		for (uint i = 0; i < that.length(); i++)
			(*this)[i] = that[i];
	}

	void vec3::set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3::operator LuaUserdata<vec3>()
	{
		MAKE_LUA_INSTANCE_RET(vec3,ret);
		LUA_VECTOR_BIND(vec3,ret,X);
		LUA_VECTOR_BIND(vec3,ret,Y);
		LUA_VECTOR_BIND(vec3,ret,Z);

		LUA_VECTOR_BIND(vec3,ret,R);
		LUA_VECTOR_BIND(vec3,ret,G);
		LUA_VECTOR_BIND(vec3,ret,B);

		return ret;
	}

	vec3::~vec3()
	{
		LUA_OBJECT_END(vec3);
	}

	vec3::vec3(const vec3& that)
	{
		set(that); LUA_OBJECT_START(vec3);
	}

	vec3::vec3(float x, float y, float z)
	{
		set(x,y,z); LUA_OBJECT_START(vec3);
	}

	vec3::vec3(const glm::vec3& that)
	{
		set(that); LUA_OBJECT_START(vec3);
	}

	vec3::vec3()
	{
		LUA_OBJECT_START(vec3);
	}
}