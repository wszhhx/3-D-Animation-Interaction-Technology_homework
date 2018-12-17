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
	glewInit();
	printf("%s\n", glGetString(GL_VERSION));
	
	
	glfwSwapInterval(1);
	
	/*glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);*/
	
	/*ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,"demo_vertex.vert"},
		{GL_FRAGMENT_SHADER,"demo_fragment.frag"},
		{GL_NONE, NULL}
	};*/
	//program = LoadShaders(shaders);

	
	/*glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
		sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 5, (void*)(sizeof(float) * 2));*/

	

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}