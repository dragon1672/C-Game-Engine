#pragma once

#include <glm/glm.hpp>
#include <Engine/Tools/BindFloat.h>
#include <Engine/Tools/MasterLua.h>

#define MAKE_GETTER_SETTER(Uppercase,LowerCase)\
	float get##Uppercase##() { return LowerCase; }                 \
	void  set##Uppercase##(float LowerCase) { this->LowerCase = LowerCase; }
#define LUA_STRING(x) #x
#define LUA_GLEW(a,b) LUA_STRING(a##b)
#define LUA_VECTOR_BIND(vec_type,var_name,UppercaseLetter)\
	var_name.Bind(LUA_GLEW(set,UppercaseLetter),&##vec_type##::set##UppercaseLetter##);\
	var_name.Bind(LUA_GLEW(get,UppercaseLetter),&##vec_type##::get##UppercaseLetter##)

namespace wrap {

	class vec2 {
	private:
		glm::vec2 back;
	public:
		union {
			struct {
				BoundFloat x;
				BoundFloat y;
			};
			struct {
				BoundFloat r;
				BoundFloat g;
			};
		};
		vec2() :
			x(back.x),	r(back.x),
			y(back.y),	g(back.y)
		{}
		MAKE_GETTER_SETTER(X,x);
		MAKE_GETTER_SETTER(Y,y);

		MAKE_GETTER_SETTER(R,r);
		MAKE_GETTER_SETTER(G,g);
		void  set(float x, float y) {
			this->x = x;
			this->y = y;
		}
		inline operator glm::vec2&() { return back; }

		inline operator LuaUserdata<vec2>() {
			MAKE_LUA_INSTANCE_RET(vec2,ret);
			LUA_VECTOR_BIND(vec2,ret,X);
			LUA_VECTOR_BIND(vec2,ret,Y);
			
			LUA_VECTOR_BIND(vec2,ret,R);
			LUA_VECTOR_BIND(vec2,ret,G);

			return ret;
		}
	};

	class vec3 {
	private:
		glm::vec3 back;
	public:
		union {
			struct {
				BoundFloat x;
				BoundFloat y;
				BoundFloat z;
			};
			struct {
				BoundFloat r;
				BoundFloat g;
				BoundFloat b;
			};
		};
		vec3() :
			x(back.x),	r(back.x),
			y(back.y),	g(back.y),
			z(back.z),	b(back.z)
		{}
		MAKE_GETTER_SETTER(X,x);
		MAKE_GETTER_SETTER(Y,y);
		MAKE_GETTER_SETTER(Z,z);

		MAKE_GETTER_SETTER(R,r);
		MAKE_GETTER_SETTER(G,g);
		MAKE_GETTER_SETTER(B,b);
		void  set(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
		inline operator glm::vec3&() { return back; }

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

	class vec4 {
	private:
		glm::vec4 back;
	public:
		union {
			struct {
				BoundFloat x;
				BoundFloat y;
				BoundFloat z;
				BoundFloat w;
			};
			struct {
				BoundFloat r;
				BoundFloat g;
				BoundFloat b;
				BoundFloat a;
			};
		};
		vec4() :
			x(back.x),	r(back.x),
			y(back.y),	g(back.y),
			z(back.z),	b(back.z),
			w(back.w),	a(back.w)
		{}
		MAKE_GETTER_SETTER(X,x);
		MAKE_GETTER_SETTER(Y,y);
		MAKE_GETTER_SETTER(Z,z);
		MAKE_GETTER_SETTER(W,w);

		MAKE_GETTER_SETTER(R,r);
		MAKE_GETTER_SETTER(G,g);
		MAKE_GETTER_SETTER(B,b);
		MAKE_GETTER_SETTER(A,a);
		void  set(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		inline operator glm::vec4&() { return back; }

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