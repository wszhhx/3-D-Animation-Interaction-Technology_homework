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
#include "PlanetData.h"
#include "PublicData.h"

#include <stdlib.h>
#include <stdio.h>

Camera camera = Camera(1.0, 40);

static void error_callback(int error, const char* description);
static void mouse_move_callback(GLFWwindow* window, double xPos, double yPos);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void DrawPlanet(int, GLuint[], GLuint[], GLuint[]);
void InitTextures(GLuint[]);
void InitPlanets();

int main()
{
	//===================================================================================环境初始化内容
	GLFWwindow *mainWindow;
	
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
	//Sun.PrintVertexInfo();
	//===========================================================================OpenGL数据内容
	
	GLuint VAOs[2];
	GLuint VBOs[2];
	GLuint textures[2];
	
	InitPlanets();

	glGenVertexArrays(2, VAOs);

	glGenBuffers(2, VBOs);

	InitTextures(textures);
	
	//================================================================================================================

	program = LoadShaders(planetShaders);

	glEnable(GL_DEPTH_TEST);
	glUseProgram(program);
	//camera.FocusPlanet(mercury);


	//===========================================================================
	while (!glfwWindowShouldClose(mainWindow)) {
		
		deltaTime = (GLfloat)glfwGetTime() - lastTime;
		lastTime = (GLfloat)glfwGetTime();
		

		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		

		//std::cout << *(glm::value_ptr(planetEntities[mercury].coreData.position)+1) << std::endl;
		planetEntities[sun].coreData.UpdateData();
		planetEntities[mercury].coreData.UpdateData();
		if (camera.focusPlanet != -1) {
			camera.updateSphericalCoord();
		}
		DrawPlanet(sun, VAOs, VBOs, textures);
		DrawPlanet(mercury, VAOs, VBOs, textures);
		
		
		glfwSwapBuffers(mainWindow);
		//glFinish();
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

void DrawPlanet(int planet, GLuint VAOs[], GLuint VBOs[], GLuint textures[]) {

	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 model = glm::mat4(1);

	model = planetEntities[planet].coreData.rotateMatrix;
	model = glm::translate(model, planetEntities[planet].coreData.position);

	//model = glm::translate(model, planetEntities[planet].coreData.position);
	//model = planetEntities[planet].coreData.rotateMatrix * model;
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

	glBindVertexArray(VAOs[planet]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[planet]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * planetEntities[planet].vertexVector.size(), planetEntities[planet].vertexArray, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(textCoord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(textCoord);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[planet]);
	glDrawArrays(GL_TRIANGLES, 0, planetEntities[planet].vertexNum);

}

void InitTextures(GLuint textures[]) {
	glGenTextures(2, textures);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// 纹理文件加载部分
	GLubyte *ImgData;
	int imgWidth, imgHeight;

	glBindTexture(GL_TEXTURE_2D, textures[sun]);
	ImgData = SOIL_load_image("textureImg-2k/太阳.jpg", &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, ImgData);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(ImgData);
	ImgData = NULL;

	glBindTexture(GL_TEXTURE_2D, textures[mercury]);
	ImgData = SOIL_load_image("textureImg-2k/水星.jpg", &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, ImgData);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(ImgData);
	ImgData = NULL;
}

void InitPlanets() {

	planetEntities[sun] = SphereGenerator(10, 64);
	planetEntities[sun].coreData = PlanetData(DAY_PER_SECOND, 25, 1, 0, 0, true);

	planetEntities[mercury] = SphereGenerator(0.35, 64);
	planetEntities[mercury].coreData = PlanetData(DAY_PER_SECOND, 59, 88, 33, 0, true);
}

