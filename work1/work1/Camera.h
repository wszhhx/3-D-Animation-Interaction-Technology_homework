#pragma once
#include<gl/GL.h>
#include<glm/glm.hpp>
class Camera
{
public:
	Camera();
	~Camera();
private:
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 viewUp;
};

