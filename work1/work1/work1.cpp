//#include <glad/glad.h>
#define GLEW_STATIC 
#include <iostream>


#include <GL/glew.h>
#include <GLFW/glfw3.h>


//#include <MATH/linmath.h>
#include <Eigen/Dense>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "MyShaderLoader.h"
#include <stdlib.h>
#include <stdio.h>

enum Shape{cube, teapot};           //标示存放不同形状的顶点数组对象的编号
enum AttribIds{vPosition = 0};		//为各个与Shader进行交互的变量进行定位，以和布局限定符layout(location = ?)对应，进行共同作用

GLfloat cubeVertices[][3] = {
	{-0.5f, -0.5f, -0.5f},
	{0.5f, -0.5f, -0.5f},
	{0.5f, 0.5f, -0.5f},
	{0.5f, 0.5f, -0.5f},
	{-0.5f, 0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},

	{-0.5f, -0.5f, 0.5f},
	{0.5f, -0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f},
	{-0.5f, 0.5f, 0.5f},
	{-0.5f, -0.5f, 0.5f},

	{-0.5f, 0.5f, 0.5f},
	{-0.5f, 0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f, 0.5f},
	{-0.5f, 0.5f, 0.5f},

	{0.5f, 0.5f, 0.5f},
	{0.5f, 0.5f, -0.5f},
	{0.5f, -0.5f, -0.5f},
	{0.5f, -0.5f, -0.5f},
	{0.5f, -0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f},

	{-0.5f, -0.5f, -0.5f},
	{0.5f, -0.5f, -0.5f},
	{0.5f, -0.5f, 0.5f},
	{0.5f, -0.5f, 0.5f},
	{-0.5f, -0.5f, 0.5f},
	{-0.5f, -0.5f, -0.5f},

	{-0.5f, 0.5f, -0.5f},
	{0.5f, 0.5f, -0.5f},
	{0.5f, 0.5f, 0.5f},
	{0.5f, 0.5f, 0.5f},
	{-0.5f, 0.5f, 0.5f},
	{-0.5f, 0.5f, -0.5f},
};

ShaderInfo cubeShaderInfo[] = {
	{GL_VERTEX_SHADER,"cube_vertex.vert",0},
	{GL_FRAGMENT_SHADER,"cube_fragment.frag",0} 
};

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(800, 800, "work1", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("error:glew初始化失败\n");
	}
	printf("%s\n", glGetString(GL_VERSION));

	GLuint VAOs[2];
	GLuint VBOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);

	GLuint program = LoadShaders(cubeShaderInfo);
	glUseProgram(program);
	glClearColor(1, 1, 1, 1);
	
	
	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//glUseProgram(program);
		
		glm::mat4 transform;
		transform = glm::rotate(transform, 100*(float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));

		GLuint transformLoc = glGetUniformLocation(program, "transform");

		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));


		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}