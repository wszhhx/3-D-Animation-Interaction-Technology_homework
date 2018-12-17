//#include <glad/glad.h>
#define GLEW_STATIC 
#include <iostream>


#include <GL/glew.h>
#include <GLFW/glfw3.h>


//#include <MATH/linmath.h>
#include <Eigen/Dense>

#include "MyShaderLoader.h"
#include <stdlib.h>
#include <stdio.h>

enum Shape{cube, teapot};

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
	window = glfwCreateWindow(1920, 1080, "work1", NULL, NULL);

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
	glBindVertexArray(VAOs[0]);

	for (int i = 0; i < 2; ++i) {
		if (glIsVertexArray(VAOs[i]))
			std::cout << "true" << std::endl;
	}

	glClearColor(1, 1, 1, 1);
	
	

	

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		glEnable(GL_LINE_STIPPLE);
		GLushort  patn = 0xFAFA;
		glLineStipple(3, patn);
		glColor3f(1.0, 0.0, 0.0);

		glBegin(GL_LINE_LOOP);
		glVertex2i(10, 10);
		glVertex2f(100.0, 75.3);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i(70, 80);
		glEnd();

		glFlush();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}