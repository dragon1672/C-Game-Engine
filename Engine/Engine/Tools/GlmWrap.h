#pragma once

#include <glm/glm.hpp>
#include <Engine/Tools/MasterLua.h>
#include <Engine/TypeDefs.h>
#include <luareference.h>

namespace wrap {

	class ENGINE_SHARED vec2 : public glm::vec2 {
		LUA_OBJECT(vec2);
	public:
		vec2() { LUA_OBJECT_START(vec2); }
		vec2(glm::vec2& that) { set(that); LUA_OBJECT_START(vec2); }
		vec2(float x, float y) { set(x,y); LUA_OBJECT_START(vec2); }
		~vec2() { LUA_OBJECT_END(vec2); }
		inline operator glm::vec2&() { return *reinterpret_cast<glm::vec2*>(this); }
		inline operator glm::vec2()  { return *reinterpret_cast<glm::vec2*>(this); }
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

	class ENGINE_SHARED vec3 : public glm::vec3 {
		LUA_OBJECT(vec3);
	public:
		vec3();
		vec3(const glm::vec3& that);
		vec3(float x, float y, float z);
		vec3(const vec3& that);
		~vec3();
		inline operator glm::vec3&() { LUA_OBJECT_END(vec3); return *reinterpret_cast<glm::vec3*>(this); }
		inline operator glm::vec3()  { LUA_OBJECT_END(vec3); return *reinterpret_cast<glm::vec3*>(this); }
		vec3& operator=(const glm::vec3& that);
		vec3& operator=(const vec3& that);
		LUA_VECTOR_MAKE_GETTER_SETTER(X,x);
		LUA_VECTOR_MAKE_GETTER_SETTER(Y,y);
		LUA_VECTOR_MAKE_GETTER_SETTER(Z,z);

		LUA_VECTOR_MAKE_GETTER_SETTER(R,r);
		LUA_VECTOR_MAKE_GETTER_SETTER(G,g);
		LUA_VECTOR_MAKE_GETTER_SETTER(B,b);
		void  set(const glm::vec3& that);
		void  set(float x, float y, float z);

		operator LuaUserdata<vec3>();
	};

	class ENGINE_SHARED vec4 : public glm::vec4 {
		LUA_OBJECT(vec4);
	public:
		vec4() { LUA_OBJECT_START(vec4); }
		vec4(glm::vec4& that) { set(that); LUA_OBJECT_START(vec4); }
		vec4(float x, float y, float z, float w) { set(x,y,z,w); LUA_OBJECT_START(vec4); }
		~vec4() { LUA_OBJECT_END(vec4); }
		inline operator glm::vec4&() { return *reinterpret_cast<glm::vec4*>(this); }
		inline operator glm::vec4()  { return *reinterpret_cast<glm::vec4*>(this); }
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