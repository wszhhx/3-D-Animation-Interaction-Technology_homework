//#include <glad/glad.h>
#define GLEW_STATIC 
#include <iostream>


#include <GL/glew.h>
#include <GLFW/glfw3.h>


//#include <MATH/linmath.h>

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"					//自己定义的相机
#include "MyShaderLoader.h"			//自己定义的Shader语言文件加载工具

#include <stdlib.h>
#include <stdio.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

enum Shape{cube, teapot};           //标示存放不同形状的顶点数组对象的编号
enum AttribIds{vPosition = 0};		//为各个与Shader进行交互的变量进行定位，以和布局限定符layout(location = ?)对应，进行共同作用

Camera camera = Camera(0.2);
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
GLfloat deltaTime;

ShaderInfo cubeShaderInfo[] = {
	{GL_VERTEX_SHADER,"cube_vertex.vert",0},
	{GL_FRAGMENT_SHADER,"cube_fragment.frag",0} 
};

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void mouse_move_callback(GLFWwindow* window, double xPos, double yPos) {
	camera.handleMouseMove((float)xPos, (float)yPos);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
	{  //关闭窗口，退出程序
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		return;
	}
	if (action == GLFW_REPEAT) {
		camera.handleKeyPress(key, deltaTime);
	}
	
}


int main(void)
{
	GLFWwindow* window;
	GLfloat lastTime = 0;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3.3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "work1", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("error:glew初始化失败\n");
	}
	printf("OpenGL:%s\n", glGetString(GL_VERSION));

	GLuint VAO;
	GLuint VBO;
	glGenVertexArrays(2, &VAO);
	glGenBuffers(2, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);

	GLuint program = LoadShaders(cubeShaderInfo);
	
	glClearColor(1, 1, 1, 1);
	
	//glEnable(GL_DEPTH_TEST);  //无光照无贴图，暂时不用开启这两个功能
	//glEnable(GL_LIGHTING);

	while (!glfwWindowShouldClose(window))
	{
		deltaTime = (GLfloat)glfwGetTime() - lastTime;
		lastTime = (GLfloat)glfwGetTime();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::mat4 view;
		glm::mat4 projection;

		view = glm::lookAt(camera.position, camera.position + camera.forward, camera.viewUp);
		projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		glUseProgram(program);

		GLuint modelLoc = glGetUniformLocation(program, "model");
		GLuint viewLoc = glGetUniformLocation(program, "view");
		GLuint projectionLoc = glGetUniformLocation(program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}