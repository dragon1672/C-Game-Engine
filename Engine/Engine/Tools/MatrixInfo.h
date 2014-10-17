#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <ExportHeader.h>
#include <Engine/Defines/VecGetSet.h>
#include <Engine/Entity/Component.h>
#include <Engine/Tools/GlmWrap.h>


#define GET_SET_TRACK(var_type,set_set_type, name,Uppercase_name)\
	var_type name;                                          \
	bool name##Changed;                                     \
	inline var_type get##Uppercase_name##() { return name; } \
	inline LuaUserdata<var_type> getLua##Uppercase_name##() { return name; } \
	inline void set##Uppercase_name##(##set_set_type##& toSet) { name = toSet; name##Changed = true; }


class ENGINE_SHARED MatrixInfo : public Component {
private:
	glm::mat4 transform;
	glm::mat4 rotationMat;
	glm::mat4 translationMat;
	glm::mat4 scaleMat;

	wrap::vec3 pos_old;
	wrap::vec3 rot_old;
	wrap::vec3 scale_old;
public:
	wrap::vec3 pos;
	wrap::vec3 rot;
	wrap::vec3 scale;

	GET_LUA_VER(wrap::vec3,pos  );
	GET_LUA_VER(wrap::vec3,scale);
	GET_LUA_VER(wrap::vec3,rot  );

	MatrixInfo() : scale(1,1,1) {}

	glm::mat4& getTransform();// save this on in the Shader

	glm::mat4&  getRotMat();
	glm::mat4&  getScaleMat();
	glm::mat4&  getTranslationMat();
	glm::mat4&  getCompleteTransform();

	//called by renderer in draw before passing uniforms to shader
	void lateUpdate();
		
	inline operator LuaUserdata<MatrixInfo>() {
		MAKE_LUA_INSTANCE_RET(MatrixInfo,ret);

		BIND_LUA_VER(MatrixInfo,ret,pos  ); // myObj.pos()
		BIND_LUA_VER(MatrixInfo,ret,scale);
		BIND_LUA_VER(MatrixInfo,ret,rot  );

		return ret;
	}
};