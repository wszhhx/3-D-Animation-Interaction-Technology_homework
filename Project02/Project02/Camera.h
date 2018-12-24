#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
class Camera
{
public:
	Camera(float,float);
	~Camera();

	glm::vec3 position;					//��¼�����������
	glm::vec3 forward;					//��¼�����ǰ���ķ��򣨵�λ������
	glm::vec3 viewUp;					//��¼������Ϸ��ķ��򣨵�λ������

	void handleMouseMove(float, float); //��������ƶ��¼�������Ƕȱ任��
	void handleKeyPress(int, GLfloat);  //������̰����¼������λ�ñ任��
	void updateVector();
private:
	float MAX_PITCH_ANGLE;				//����������������趨���������Ϊ89��
	
	glm::vec2 lastMousePosition;		//��¼��һ֡���λ��
	glm::vec3 side;						//��¼������ҷ��ķ��򣨵�λ������
	
	float pitchAngle;					//�����x����ת�ĽǶ�
	float yawAngle;						//�����y����ת�ĽǶ�
	float moveSpeed;

	bool firstMouseMove;				//����Ƿ��ǵ�һ���ƶ�
	float mouseSensitivity;				//��¼���������
};

