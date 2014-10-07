#pragma once

#include <Engine\Entity\Component.h>

class MatrixInfoComponent : public Component {
public:
	private:
	glm::mat4 transform;
	glm::mat4 rotationMat;
	glm::mat4 translationMat;
	glm::mat4 scaleMat;
	
	glm::vec3 position;
	bool posChanged;
	glm::vec3 rotation;
	bool rotChanged;
	glm::vec3 scale;
	bool scaleChanged;

public:
	MatrixInfoComponent() : scale(1,1,1), posChanged(true), rotChanged(true), scaleChanged(true) {}

	inline float     getRotX() { return rotation.x; }
	inline float     getRotY() { return rotation.y; }
	inline float     getRotZ() { return rotation.z; }
	inline glm::vec3 getRot()  { return rotation;   }
	
	inline void setRotX(float x) { rotation.x = x; rotChanged = true; }
	inline void setRotY(float y) { rotation.y = y; rotChanged = true; }
	inline void setRotZ(float z) { rotation.z = z; rotChanged = true; }
	inline void setRot(float x, float y, float z) { rotation = glm::vec3(x,y,z); }
	
	inline float     getScaleX() { return scale.x; }
	inline float     getScaleY() { return scale.y; }
	inline float     getScaleZ() { return scale.z; }
	inline glm::vec3 getScale()  { return scale;   }

	inline void setScaleX(float x) { scale.x = x; scaleChanged = true; }
	inline void setScaleY(float y) { scale.y = y; scaleChanged = true; }
	inline void setScaleZ(float z) { scale.z = z; scaleChanged = true; }
	inline void setScale(float x, float y, float z) { scale = glm::vec3(x,y,z); }
	
	inline float     getPosX() { return position.x; }
	inline float     getPosY() { return position.y; }
	inline float     getPosZ() { return position.z; }
	inline glm::vec3 getPos()  { return position;   }

	inline void setPosX(float x) { position.x = x; posChanged = true; }
	inline void setPosY(float y) { position.y = y; posChanged = true; }
	inline void setPosZ(float z) { position.z = z; posChanged = true; }
	inline void setPos(float x, float y, float z)  { position = glm::vec3(x,y,z); }

	glm::mat4& getTransform();// save this on in the Shader

	glm::mat4&  getRotMat();
	glm::mat4&  getScaleMat();
	glm::mat4&  getTranslationMat();
	glm::mat4&  getCompleteTransform();

	//called by renderer in draw before passing uniforms to shader
	void lateUpdate();
};