#include "SphereGenerator.h"
#include "glm/glm.hpp"
#define PI 3.1415926

SphereGenerator::SphereGenerator(float radius,int stepnum)
{
	if (stepnum < 4) {
		printf("error: in SphereGenerator() ������С��\n");
		exit(0);
	}
	stepNum = stepnum;
	stepY = PI / (stepNum + 1);
	stepRzx = PI / (stepNum);

	stepS = 1.0 / (2 * stepNum);
	stepT = 1.0 / (stepNum + 1);

	float theta = 0;
	float gama = stepY;


	vertexArray = NULL;
	vertexNum = 0;
	for (int i = 0; i < 2 * stepNum; ++i) {	//���������϶˵���������
		theta = i * stepRzx;
		
		vertexVector.push_back(radius * sin(gama) * sin(theta));	
		vertexVector.push_back(radius * cos(gama));					
		vertexVector.push_back(radius * sin(gama) * cos(theta));	
		for (int j = 0; j < 3; ++j)		
			vertexVector.push_back(0.0);
		vertexVector.push_back(i*stepS);
		vertexVector.push_back(stepT);
		vertexNum++;

		vertexVector.push_back(radius * sin(gama) * sin(theta + stepRzx));	
		vertexVector.push_back(radius * cos(gama));						
		vertexVector.push_back(radius * sin(gama) * cos(theta + stepRzx));	
		for (int j = 0; j < 3; ++j)		
			vertexVector.push_back(0.0);
		vertexVector.push_back(i*stepS + stepS);
		vertexVector.push_back(stepT);
		vertexNum++;

		vertexVector.push_back(0.0);				//x
		vertexVector.push_back(radius);				//y
		vertexVector.push_back(0.0);				//z
		for (int j = 0; j < 3; ++j)		//Ϊrgb����Ԥ���ռ�
			vertexVector.push_back(0.0);
		vertexVector.push_back(i*stepS);//s
		vertexVector.push_back(0);					//t
		vertexNum++;
	}

	for (int i = 1; i < stepNum; ++i) {	//���������м�������滷��		
		gama = i * stepY;
		for (int j = 0; j < 2 * stepNum; ++j) {	//��������һȦ���ǻ���
			theta = j * stepRzx;
			//���·�������Ƭ
			//	1
			vertexVector.push_back(radius * sin(gama) * sin(theta));	
			vertexVector.push_back(radius * cos(gama));					
			vertexVector.push_back(radius * sin(gama) * cos(theta));	
			for (int j = 0; j < 3; ++j)		
				vertexVector.push_back(0.0);
			vertexVector.push_back(j * stepS);
			vertexVector.push_back(i * stepT);
			vertexNum++;
			//	2
			vertexVector.push_back(radius * sin(gama + stepY) * sin(theta));	
			vertexVector.push_back(radius * cos(gama + stepY));					
			vertexVector.push_back(radius * sin(gama + stepY) * cos(theta));	
			for (int j = 0; j < 3; ++j)		
				vertexVector.push_back(0.0);
			vertexVector.push_back(j * stepS);
			vertexVector.push_back(i*stepT + stepT);
			vertexNum++;
			//	3
			vertexVector.push_back(radius * sin(gama + stepY) * sin(theta + stepRzx));
			vertexVector.push_back(radius * cos(gama + stepY));
			vertexVector.push_back(radius * sin(gama + stepY) * cos(theta + stepRzx));
			for (int j = 0; j < 3; ++j)
				vertexVector.push_back(0.0);
			vertexVector.push_back(j*stepS + stepS);
			vertexVector.push_back(i*stepT + stepT);
			vertexNum++;
			//���Ϸ�������Ƭ
			//	3
			vertexVector.push_back(radius * sin(gama + stepY) * sin(theta + stepRzx));
			vertexVector.push_back(radius * cos(gama + stepY));
			vertexVector.push_back(radius * sin(gama + stepY) * cos(theta + stepRzx));
			for (int j = 0; j < 3; ++j)
				vertexVector.push_back(0.0);
			vertexVector.push_back(j*stepS + stepS);
			vertexVector.push_back(i*stepT + stepT);
			vertexNum++;

			//	4
			vertexVector.push_back(radius * sin(gama) * sin(theta + stepRzx));
			vertexVector.push_back(radius * cos(gama));
			vertexVector.push_back(radius * sin(gama) * cos(theta + stepRzx));
			for (int j = 0; j < 3; ++j)
				vertexVector.push_back(0.0);
			vertexVector.push_back(j * stepS + stepS);
			vertexVector.push_back(i * stepT);			//ԭ������ط����ǳ�i�����˼���Сʱ��ͼ���ҡ�������
			vertexNum++;
		
			//	1
			vertexVector.push_back(radius * sin(gama) * sin(theta));
			vertexVector.push_back(radius * cos(gama));
			vertexVector.push_back(radius * sin(gama) * cos(theta));
			for (int j = 0; j < 3; ++j)
				vertexVector.push_back(0.0);
			vertexVector.push_back(j * stepS);
			vertexVector.push_back(i * stepT);
			vertexNum++;
		}
	}		

	gama = PI - stepY;

	for (int i = 0; i < 2 * stepNum; ++i) {	//�����������¶˵���������
		theta = i * stepRzx;

		
		//�������·��ĵ�
		vertexVector.push_back(0);
		vertexVector.push_back(-radius);
		vertexVector.push_back(0);
		for (int j = 0; j < 3; ++j)
			vertexVector.push_back(0.0);
		vertexVector.push_back(i*stepS + stepS);
		vertexVector.push_back(1);
		vertexNum++;
		//��������
		vertexVector.push_back(radius * sin(gama) * sin(theta + stepRzx));
		vertexVector.push_back(radius * cos(gama));
		vertexVector.push_back(radius * sin(gama) * cos(theta + stepRzx));
		for (int j = 0; j < 3; ++j)
			vertexVector.push_back(0.0);
		vertexVector.push_back(i*stepS + stepS);
	    vertexVector.push_back(1 - stepT);
		vertexNum++;

		//��һ����
		vertexVector.push_back(radius * sin(gama) * sin(theta));
		vertexVector.push_back(radius * cos(gama));
		vertexVector.push_back(radius * sin(gama) * cos(theta));
		for (int j = 0; j < 3; ++j)		//Ϊrgb��st����Ԥ���ռ�
			vertexVector.push_back(0.0);
		vertexVector.push_back(i*stepS);
		vertexVector.push_back(1 - stepT);
		vertexNum++;
	}

	SynthesisArray();
}


SphereGenerator::~SphereGenerator()
{
}

void SphereGenerator::PrintVertexInfo() {
	if (vertexArray == NULL) {
		printf("error: in PrintVertexInfo() �����ڶ���������Ϣ��\n");
		return;
	}
	int index = 1;
	for (int i = 0; i < vertexNum*8; i += 8) {
		printf("���� %d ���� ����XYZ : (%.4f , %.4f, %.4f)  ����ST��(%.4f , %.4f)\n", index, vertexArray[i], vertexArray[i + 1], vertexArray[i + 2],
			vertexArray[i+6], vertexArray[i+7]);
		index += 1;
	}
}

void SphereGenerator::SynthesisArray() {
	if (vertexVector.empty()) {
		printf("error: in SynthesisArray() �����ڶ���������¼��\n");
		return;
	}
	vertexArray = (GLfloat*)malloc(sizeof(GLfloat) * vertexVector.size());
	if (vertexArray) {
		memcpy(vertexArray, &vertexVector[0], sizeof(GLfloat) * vertexVector.size());
	}
	else {
		printf("error: in SynthesisArray() ����ռ�ʧ��!\n");
	}
}