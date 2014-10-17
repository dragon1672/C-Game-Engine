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

		GET_SET_TRACK(wrap::vec3,glm::vec3,pos,Pos);
		GET_SET_TRACK(wrap::vec3,glm::vec3,rot,Rot);
		GET_SET_TRACK(wrap::vec3,glm::vec3,scale,Scale);

	public:
		MatrixInfo() : scale(1,1,1), posChanged(true), rotChanged(true), scaleChanged(true) {}

		glm::mat4& getTransform();// save this on in the Shader

		glm::mat4&  getRotMat();
		glm::mat4&  getScaleMat();
		glm::mat4&  getTranslationMat();
		glm::mat4&  getCompleteTransform();

		//called by renderer in draw before passing uniforms to shader
		void lateUpdate();
		//LuaTable * getLuaComponent() { return LuaTable(); }
	};