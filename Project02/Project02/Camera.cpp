#include "Camera.h"



Camera::Camera(float sensivitity = 1.0, float depth = 1.0)
{
	MAX_PITCH_ANGLE = 89;

	viewUp = glm::vec3(0.0, 1.0, 0.0);
	forward = glm::normalize(glm::vec3(0.0, 0.0, -1.0));
	side = glm::vec3(1.0, 0.0, 0.0);
	position = glm::vec3(0.0, 0.0, depth);

	focusPlanet = NULL;
	
	firstMouseMove = true;
	mouseSensitivity = sensivitity;
	moveSpeed = 2;
}


Camera::~Camera()
{
}

void Camera::handleMouseMove(float xPos, float yPos)
{
	if (firstMouseMove) {
		lastMousePosition.x = xPos;
		lastMousePosition.y = yPos;
		firstMouseMove = false;
	}

	GLfloat xOffset = lastMousePosition.x - xPos;
	GLfloat yOffset = lastMousePosition.y - yPos;

	lastMousePosition.x = xPos;
	lastMousePosition.y = yPos;

	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;
	
	pitchAngle += yOffset;
	yawAngle += xOffset;

	if (pitchAngle > MAX_PITCH_ANGLE)
		pitchAngle = MAX_PITCH_ANGLE;
	if (pitchAngle < -MAX_PITCH_ANGLE)
		pitchAngle = -MAX_PITCH_ANGLE;
	if (yawAngle > 360)
		yawAngle -= 360;
	if (yawAngle < 0)
		yawAngle += 360;
	updateVector();
}

void Camera::handleKeyPress(int key, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;
	switch (key)
	{
	case GLFW_KEY_W:
		position += forward * velocity;
		break;
	case GLFW_KEY_S:
		position -= forward * velocity;
		break;
	case GLFW_KEY_A:
		position -= side * velocity;
		break;
	case GLFW_KEY_D:
		position += side * velocity;
		break;
	default:
		break;
	}
	//printf("( %f , %f , %f )\n", position.x, position.y, position.z);
}

void Camera::updateVector()
{
	glm::vec3 newForward;
	newForward.x = -sin(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));
	newForward.y = sin(glm::radians(pitchAngle));
	newForward.z = -cos(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));
	forward = glm::normalize(newForward);

	glm::vec3 newSide;
	newSide.x = cos(glm::radians(yawAngle));
	newSide.y = 0.0;
	newSide.z = -sin(glm::radians(yawAngle));
	side = glm::normalize(newSide);
}

void Camera::FocusPlanet(SphereGenerator* planet) {	//摄像机跟随某星球
	focusPlanet = planet;

	glm::mat4 camTrans = glm::mat4(1);
	glm::vec3 transVec = (planet->coreData.position - position) -
		glm::normalize(planet->coreData.position - position) * planet->radius * (GLfloat)2.0;
	camTrans = glm::translate(camTrans, transVec);
	position = camTrans * glm::vec4(position,1.0);
	
	forward = glm::normalize(planet->coreData.position - position);
	glm::mat4 tempRotate = glm::mat4(0, 0, 1, 0, 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1);
	//tempRotate = glm::rotate(tempRotate, glm::radians(-90.0), glm::vec3(0, 1, 0));   //为何同样的参数类型其他地方都不会报参数错误，只有这里会报，MMP
	side = glm::vec4(forward, 1.0) * tempRotate;
}


