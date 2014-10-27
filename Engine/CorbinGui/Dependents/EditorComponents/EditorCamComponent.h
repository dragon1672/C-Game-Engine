#pragma once

#include <Engine/Entity/Components/CameraComponent.h>
#include <Engine/Entity/Components/RenderableComponent.h>

class ENGINE_SHARED EditorCamComponent : public Component {
	CameraComponent * cam;
	RenderableComponent * renderableForCam;
public:
	EditorCamComponent(const char * myName, CameraComponent * cam, RenderableComponent * renderableForCam) {
		this->cam = cam;
		this->renderableForCam = renderableForCam;
	}

	virtual void earlyUpdate()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual bool isValid()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual void init()
	{
		renderableForCam->addUniformParameter("cam_farPlane", cam->farPlane );
		renderableForCam->addUniformParameter("cam_nearPlane",cam->nearPlane);
		renderableForCam->addUniformParameter("cam_width",    cam->width    );
		renderableForCam->addUniformParameter("cam_height",   cam->height   );
	}

};