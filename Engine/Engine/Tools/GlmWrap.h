#pragma once

#include <glm/glm.hpp>
#include <Engine/Tools/MasterLua.h>
#include <Engine/TypeDefs.h>

#define LUA_VECTOR_MAKE_GETTER_SETTER(Uppercase,LowerCase)\
	inline float get##Uppercase##() { return LowerCase; }                 \
	inline void  set##Uppercase##(float LowerCase) { this->LowerCase = LowerCase; }
#define LUA_STRING(x) #x
#define LUA_GLEW(a,b) LUA_STRING(a##b)
#define LUA_VECTOR_BIND(vec_type,var_name,UppercaseLetter)\
	var_name.Bind(LUA_GLEW(set,UppercaseLetter),&##vec_type##::set##UppercaseLetter##);\
	var_name.Bind(LUA_GLEW(get,UppercaseLetter),&##vec_type##::get##UppercaseLetter##)

namespace wrap {

	class vec2 : glm::vec2 {
	public:
		vec2() { }
		vec2(glm::vec2& that) { set(that); }
		vec2(float x, float y) { set(x,y); }
		inline operator glm::vec2&() { return *reinterpret_cast<glm::vec2*>(this); }
		vec2& operator=(const glm::vec2& that) { set(that); return *this; }
		LUA_VECTOR_MAKE_GETTER_SETTER(X,x);
		LUA_VECTOR_MAKE_GETTER_SETTER(Y,y);

		LUA_VECTOR_MAKE_GETTER_SETTER(R,r);
		LUA_VECTOR_MAKE_GETTER_SETTER(G,g);

		void  set(const glm::vec2& that) {
			for (uint i = 0; i < that.length(); i++)
				(*this)[i] = that[i];
		}
		void  set(float x, float y) {
			this->x = x;
			this->y = y;
		}

		inline operator LuaUserdata<vec2>() {
			MAKE_LUA_INSTANCE_RET(vec2,ret);
			LUA_VECTOR_BIND(vec2,ret,X);
			LUA_VECTOR_BIND(vec2,ret,Y);
			
			LUA_VECTOR_BIND(vec2,ret,R);
			LUA_VECTOR_BIND(vec2,ret,G);

			return ret;
		}
	};

	class vec3 : public glm::vec3 {
	public:
		vec3() { }
		vec3(glm::vec3& that) { set(that); }
		vec3(float x, float y, float z) { set(x,y,z); }
		inline operator glm::vec3&() { return *reinterpret_cast<glm::vec3*>(this); }
		vec3& operator=(const glm::vec3& that) { set(that); return *this; }
		LUA_VECTOR_MAKE_GETTER_SETTER(X,x);
		LUA_VECTOR_MAKE_GETTER_SETTER(Y,y);
		LUA_VECTOR_MAKE_GETTER_SETTER(Z,z);

		LUA_VECTOR_MAKE_GETTER_SETTER(R,r);
		LUA_VECTOR_MAKE_GETTER_SETTER(G,g);
		LUA_VECTOR_MAKE_GETTER_SETTER(B,b);
		void  set(const glm::vec3& that) {
			for (uint i = 0; i < that.length(); i++)
				(*this)[i] = that[i];
		}
		void  set(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		inline operator LuaUserdata<vec3>() {
			MAKE_LUA_INSTANCE_RET(vec3,ret);
			LUA_VECTOR_BIND(vec3,ret,X);
			LUA_VECTOR_BIND(vec3,ret,Y);
			LUA_VECTOR_BIND(vec3,ret,Z);

			LUA_VECTOR_BIND(vec3,ret,R);
			LUA_VECTOR_BIND(vec3,ret,G);
			LUA_VECTOR_BIND(vec3,ret,B);

			return ret;
		}
	};

	class vec4 : public glm::vec4 {
	public:
		vec4() { }
		vec4(glm::vec4& that) { set(that); }
		vec4(float x, float y, float z, float w) { set(x,y,z,w); }
		inline operator glm::vec4&() { return *reinterpret_cast<glm::vec4*>(this); }
		vec4& operator=(const glm::vec4& that) { set(that); return *this; }
		LUA_VECTOR_MAKE_GETTER_SETTER(X,x);
		LUA_VECTOR_MAKE_GETTER_SETTER(Y,y);
		LUA_VECTOR_MAKE_GETTER_SETTER(Z,z);
		LUA_VECTOR_MAKE_GETTER_SETTER(W,w);

		LUA_VECTOR_MAKE_GETTER_SETTER(R,r);
		LUA_VECTOR_MAKE_GETTER_SETTER(G,g);
		LUA_VECTOR_MAKE_GETTER_SETTER(B,b);
		LUA_VECTOR_MAKE_GETTER_SETTER(A,a);
		void  set(const glm::vec4& that) {
			for (uint i = 0; i < that.length(); i++)
				(*this)[i] = that[i];
		}
		void  set(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		inline operator LuaUserdata<vec4>() {
			MAKE_LUA_INSTANCE_RET(vec4,ret);
			LUA_VECTOR_BIND(vec4,ret,X);
			LUA_VECTOR_BIND(vec4,ret,Y);
			LUA_VECTOR_BIND(vec4,ret,Z);
			LUA_VECTOR_BIND(vec4,ret,W);

			LUA_VECTOR_BIND(vec4,ret,R);
			LUA_VECTOR_BIND(vec4,ret,G);
			LUA_VECTOR_BIND(vec4,ret,B);
			LUA_VECTOR_BIND(vec4,ret,A);

			return ret;
		}
	};
}