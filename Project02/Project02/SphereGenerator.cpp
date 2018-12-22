#include "SphereGenerator.h"
#include "glm/glm.hpp"
#define PI 3.1415926

SphereGenerator::SphereGenerator(float radius,int stepnum)
{
	if (stepnum < 4) {
		printf("error: in SphereGenerator() 步长过小！\n");
	}
	stepNum = stepnum;
	stepY = PI / stepNum;
	stepRzx = PI / stepNum;

	stepS = 1.0 / (2 * stepNum);
	stepT = 1.0 / stepNum;

	float theta = 0;
	float gama = stepY;


	vertexArray = NULL;
	vertexNum = 0;
	for (int i = 0; i < 2 * stepNum; ++i) {	//计算球体上端的三角网格
		theta = i * stepRzx;
		//y轴最上方顶点
		vertexVector.push_back(0.0);				//x
		vertexVector.push_back(radius);				//y
		vertexVector.push_back(0.0);				//z
		for (int j = 0; j < 3; ++j)		//为rgb坐标预留空间
			vertexVector.push_back(0.0);
		vertexVector.push_back(i*stepS + stepS / 2);//s
		vertexVector.push_back(0);					//t
		vertexNum++;
		//第二个点
		vertexVector.push_back(radius * sin(gama) * sin(theta));	
		vertexVector.push_back(radius * cos(gama));					
		vertexVector.push_back(radius * sin(gama) * cos(theta));	
		for (int j = 0; j < 3; ++j)		
			vertexVector.push_back(0.0);
		vertexVector.push_back(0);
		vertexVector.push_back(i*stepS);
		vertexNum++;
		//第三个点
		vertexVector.push_back(radius * sin(gama) * sin(theta + stepRzx));	
		vertexVector.push_back(radius * cos(gama));						
		vertexVector.push_back(radius * sin(gama) * cos(theta + stepRzx));	
		for (int j = 0; j < 3; ++j)		
			vertexVector.push_back(0.0);
		vertexVector.push_back(i*stepS + stepS);
		vertexVector.push_back(stepT);
		vertexNum++;

	}

	for (int i = 1; i < stepNum; ++i) {	//计算球体中间的三角面环带					
		gama = i * stepY;
		for (int j = 0; j < 2 * stepNum; ++j) {	//计算其中一圈三角环带
			theta = j * stepRzx;
			//左上方三角面片
			//	第一个点
			vertexVector.push_back(radius * sin(gama) * sin(theta));	
			vertexVector.push_back(radius * cos(gama));					
			vertexVector.push_back(radius * sin(gama) * cos(theta));	
			for (int j = 0; j < 3; ++j)		
				vertexVector.push_back(0.0);
			vertexVector.push_back(j * stepS);
			vertexVector.push_back(i * stepT);
			vertexNum++;
			//	第二个点
			vertexVector.push_back(radius * sin(gama + stepY) * sin(theta));	
			vertexVector.push_back(radius * cos(gama + stepY));					
			vertexVector.push_back(radius * sin(gama + stepY) * cos(theta));	
			for (int j = 0; j < 3; ++j)		
				vertexVector.push_back(0.0);
			vertexVector.push_back(j * stepS);
			vertexVector.push_back(i*stepT + stepT);
			vertexNum++;
			//	第三个点
			vertexVector.push_back(radius * sin(gama) * sin(theta + stepRzx));
			vertexVector.push_back(radius * cos(gama));
			vertexVector.push_back(radius * sin(gama) * cos(theta + stepRzx));
			for (int j = 0; j < 3; ++j)
				vertexVector.push_back(0.0);
			vertexVector.push_back(j * stepS + stepS);
			vertexVector.push_back(stepT);
			vertexNum++;
			//右下方三角面片
			//	第一个点
			vertexVector.push_back(radius * sin(gama + stepY) * sin(theta));
			vertexVector.push_back(radius * cos(gama + stepY));
			vertexVector.push_back(radius * sin(gama + stepY) * cos(theta));
			for (int j = 0; j < 3; ++j)
				vertexVector.push_back(0.0);
			vertexVector.push_back(j * stepS);
			vertexVector.push_back(i*stepT + stepT);
			vertexNum++;
			//	第二个点
			vertexVector.push_back(radius * sin(gama + stepY) * sin(theta + stepRzx));
			vertexVector.push_back(radius * cos(gama + stepY));
			vertexVector.push_back(radius * sin(gama + stepY) * cos(theta + stepRzx));
			for (int j = 0; j < 3; ++j)
				vertexVector.push_back(0.0);
			vertexVector.push_back(j*stepS + stepS);
			vertexVector.push_back(i*stepT + stepT);
			vertexNum++;
			//	第三个点
			vertexVector.push_back(radius * sin(gama) * sin(theta + stepRzx));
			vertexVector.push_back(radius * cos(gama));
			vertexVector.push_back(radius * sin(gama) * cos(theta + stepRzx));
			for (int j = 0; j < 3; ++j)
				vertexVector.push_back(0.0);
			vertexVector.push_back(j * stepS + stepS);
			vertexVector.push_back(stepT);
			vertexNum++;
		}
	}		

	gama = PI - stepY;

	for (int i = 0; i < 2 * stepNum; ++i) {	//计算球体最下端的三角网格
		theta = i * stepRzx;

		//第一个点
		vertexVector.push_back(radius * sin(gama) * sin(theta));			
		vertexVector.push_back(radius * cos(gama));				
		vertexVector.push_back(radius * sin(gama) * cos(theta));				
		for (int j = 0; j < 3; ++j)		//为rgb和st坐标预留空间
			vertexVector.push_back(0.0);
		vertexVector.push_back(i*stepS);
		vertexVector.push_back(1 - stepT);
		vertexNum++;
		//球体最下方的点
		vertexVector.push_back(0);
		vertexVector.push_back(radius * cos(gama));
		vertexVector.push_back(0);
		for (int j = 0; j < 3; ++j)
			vertexVector.push_back(0.0);
		vertexVector.push_back(i*stepS + stepS / 2);
		vertexVector.push_back(1);
		vertexNum++;
		//第三个点
		vertexVector.push_back(radius * sin(gama) * sin(theta + stepRzx));
		vertexVector.push_back(radius * cos(gama));
		vertexVector.push_back(radius * sin(gama) * cos(theta + stepRzx));
		for (int j = 0; j < 3; ++j)
			vertexVector.push_back(0.0);
		vertexVector.push_back(i*stepS + stepS);
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
		printf("error: in PrintVertexInfo() 不存在顶点数组信息！\n");
		return;
	}
	int index = 1;
	for (int i = 0; i < vertexNum; i += 8) {
		printf("顶点 %d —— 坐标XYZ : (%.4f , %.4f, %.4f)  纹理ST：(%.4f , %.4f)\n", index, vertexArray[i], vertexArray[i + 1], vertexArray[i + 2],
			vertexArray[i+6], vertexArray[i+7]);
		index += 1;
	}
}

void SphereGenerator::SynthesisArray() {
	if (vertexVector.empty()) {
		printf("error: in SynthesisArray() 不存在顶点向量记录！\n");
		return;
	}
	vertexArray = (GLfloat*)malloc(sizeof(GLfloat) * vertexVector.size());
	if (vertexArray) {
		memcpy(vertexArray, &vertexVector[0], sizeof(GLfloat) * vertexVector.size());
	}
	else {
		printf("error: in SynthesisArray() 申请空间失败!\n");
	}
}