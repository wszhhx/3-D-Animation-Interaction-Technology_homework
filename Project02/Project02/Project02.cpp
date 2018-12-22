#define GLEW_STATIC
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL/SOIL.h>

#include "MyShaderLoader.h"
#include "Camera.h"
#include "CallBackFuncs.h"
#include "SphereGenerator.h"

#include <stdlib.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 1024;

enum{mars = 0,test = 1};
enum{ vPosition = 0, color, textCoord };

GLfloat cubeVertices[] = {				//分别为顶点坐标（xyz）、顶点颜色值（rgb）、纹理坐标（st）、正好一行代表一个顶点共有8个分量值
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0, 1.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
};


ShaderInfo planetShaders[] = { 
	{GL_VERTEX_SHADER,"PlanetVertexShader.vert",0},
	{GL_FRAGMENT_SHADER,"PlanetFragmentShader.frag",0} 
};



int main()
{
	//===================================================================================环境初始化内容
	GLFWwindow *mainWindow;
	GLfloat lastTime = 0;
	GLfloat deltaTime;
	SphereGenerator sphere = SphereGenerator(0.5, 30);
	if (!glfwInit()) {
		printf("error: glfw初始化失败！\n");
		exit(0);
	}

	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 0);
	mainWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Project02", NULL, NULL);

	if (!mainWindow) {
		glfwTerminate();
		printf("error: glfw窗口创建失败！\n");
		exit(0);
	}

	glfwSetErrorCallback(error_callback);

	glfwMakeContextCurrent(mainWindow);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("error: glew初始化失败!\n");
		glfwTerminate();
		exit(0);
	}
	printf("OpenGL:%s\n", glGetString(GL_VERSION));
	sphere.PrintVertexInfo();
	//===========================================================================OpenGL数据内容
	GLuint VAOs[2];
	GLuint VBOs[2];
	GLuint program;
	glGenVertexArrays(2, VAOs);
	glBindVertexArray(VAOs[mars]);

	glGenBuffers(2, VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[mars]);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sphere.vertexVector.size(), sphere.vertexArray, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(vPosition);

	program = LoadShaders(planetShaders);

	glEnable(GL_DEPTH_TEST);
	glUseProgram(program);
	//===========================================================================
	while (!glfwWindowShouldClose(mainWindow)) {
		glfwPollEvents();

		deltaTime = (float)glfwGetTime() - lastTime;
		lastTime = (float)glfwGetTime();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(program);
		//glLineWidth(2);
		glDrawArrays(GL_TRIANGLES, 0, sphere.vertexNum);
		glfwSwapBuffers(mainWindow);
	}
	

}

