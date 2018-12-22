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
#include "SphereGenerator.h"

#include <stdlib.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 1024;

enum{earth = 0,mars};
enum{ vPosition = 0, color, textCoord };

Camera camera = Camera(1.0);

GLfloat deltaTime;

ShaderInfo planetShaders[] = { 
	{GL_VERTEX_SHADER,"PlanetVertexShader.vert",0},
	{GL_FRAGMENT_SHADER,"PlanetFragmentShader.frag",0} 
};

static void error_callback(int error, const char* description);
static void mouse_move_callback(GLFWwindow* window, double xPos, double yPos);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
	//===================================================================================环境初始化内容
	GLFWwindow *mainWindow;
	GLfloat lastTime = 0;
	GLfloat rotateAngle = 0;
	
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
	glfwSetKeyCallback(mainWindow, key_callback);
	glfwSetCursorPosCallback(mainWindow, mouse_move_callback);
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(mainWindow);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("error: glew初始化失败!\n");
		glfwTerminate();
		exit(0);
	}
	printf("OpenGL:%s\n", glGetString(GL_VERSION));
	//sphere.PrintVertexInfo();
	//===========================================================================OpenGL数据内容
	SphereGenerator sphere = SphereGenerator(1, 30);


	GLuint VAOs[2];
	GLuint VBOs[2];
	GLuint textures[2];
	GLuint program;
	glGenVertexArrays(2, VAOs);
	glBindVertexArray(VAOs[earth]);

	glGenBuffers(2, VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[earth]);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sphere.vertexVector.size(), sphere.vertexArray, GL_STATIC_DRAW);
	
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(textCoord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(textCoord);

	glGenTextures(2, textures);
	glBindTexture(GL_TEXTURE_2D,textures[earth]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);			
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	GLubyte *imageData = NULL;
	int imgWidth, imgHeight;
	imageData = SOIL_load_image("earth.jpg", &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(imageData);
	imageData = NULL;

	program = LoadShaders(planetShaders);

	glEnable(GL_DEPTH_TEST);
	glUseProgram(program);

	//===========================================================================
	while (!glfwWindowShouldClose(mainWindow)) {
		glfwPollEvents();

		deltaTime = (GLfloat)glfwGetTime() - lastTime;
		lastTime = (GLfloat)glfwGetTime();
		rotateAngle += 20 * deltaTime;
		if (rotateAngle > 360)
			rotateAngle -= 360;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		

		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 model = glm::mat4(1);

		model = glm::rotate(model, glm::radians(rotateAngle), glm::vec3(0, 1, 0));
		view = glm::lookAt(camera.position, camera.position + camera.forward, camera.viewUp);
		projection = glm::perspective(glm::radians(70.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		

		GLuint textureCoordLoc = glGetUniformLocation(program, "texSampler");
		GLuint modelLoc = glGetUniformLocation(program, "model");
		GLuint viewLoc = glGetUniformLocation(program, "view");
		GLuint projectionLoc = glGetUniformLocation(program, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniform1i(textureCoordLoc, 0);

		glActiveTexture(GL_TEXTURE0);
	

		glDrawArrays(GL_TRIANGLES, 0, sphere.vertexNum);
		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	exit(EXIT_SUCCESS);

}

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

