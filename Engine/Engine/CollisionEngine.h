#pragma once

class CollisionEngine {
public:
	virtual void update() = 0;
	virtual bool hasCollided() = 0;
	virtual float getPenetration() = 0;
	virtual glm::vec3 getNormal() = 0;
};