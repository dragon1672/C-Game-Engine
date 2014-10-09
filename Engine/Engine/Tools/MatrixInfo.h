#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <ExportHeader.h>
#include <Engine/Defines/VecGetSet.h>
#include <Engine/Entity/Component.h>

class ENGINE_SHARED MatrixInfo : public Component {
	private:
		glm::mat4 transform;
		glm::mat4 rotationMat;
		glm::mat4 translationMat;
		glm::mat4 scaleMat;

		GET_SET_TRACK_VEC3(pos,position);
		GET_SET_TRACK_VEC3(rot,rotation);
		GET_SET_TRACK_VEC3(scale,scale);

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