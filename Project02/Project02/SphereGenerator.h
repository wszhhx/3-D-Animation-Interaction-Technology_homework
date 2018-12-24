#pragma once

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "PlanetData.h"

class SphereGenerator
{
public:
	SphereGenerator();
	SphereGenerator(float radius,int stepnum);
	~SphereGenerator();
	std::vector<GLfloat> vertexVector;
	GLfloat *vertexArray;
	GLuint vertexNum;
	PlanetData coreData;
	GLfloat radius;
	void PrintVertexInfo();
private:
	
	int stepNum;							//γ������
	float stepRzx;							//������֮��ļ�� (Radians)
	float stepY;							//��γ��֮��ļ�� (Radians)

	float stepS;							//��������γ�ȼ�ֵ
	float stepT;							//�������꾭�ȼ�ֵ

	void SynthesisArray();
};

