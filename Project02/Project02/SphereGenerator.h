#include<GL/glew.h>
#include<iostream>
#include<vector>

class SphereGenerator
{
public:
	SphereGenerator(float radius,int stepnum);
	~SphereGenerator();
	std::vector<GLfloat> vertexVector;
	GLfloat *vertexArray;
	GLuint vertexNum;
	

	void PrintVertexInfo();
private:
	
	int stepNum;							//纬线条数
	float stepRzx;							//两经度之间的间角 (Radians)
	float stepY;								//两纬度之间的间角 (Radians)

	void SynthesisArray();
};

