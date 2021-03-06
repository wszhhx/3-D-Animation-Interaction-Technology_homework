//#include <glad/glad.h>
#define GLEW_STATIC 
#include <iostream>


#include <GL/glew.h>
#include <GLFW/glfw3.h>


//#include <MATH/linmath.h>

#include <glm/glm.hpp>
#include <SOIL/SOIL.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"					//自己定义的相机
#include "MyShaderLoader.h"			//自己定义的Shader语言文件加载工具

#include <stdlib.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

enum Shape{cube, teapot};           //标示存放不同形状的顶点数组对象的编号
enum AttribIds{vPosition = 0, color, textCoord};		//为各个与Shader进行交互的变量进行定位，以和布局限定符layout(location = ?)对应，进行共同作用

Camera camera = Camera(0.2);

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


//GLfloat cubeVertices[][3] = {		//没使用纹理数据的结构化顶点数据
//	{-0.5f, -0.5f, -0.5f},
//	{0.5f, -0.5f, -0.5f},
//	{0.5f, 0.5f, -0.5f},
//	{0.5f, 0.5f, -0.5f},
//	{-0.5f, 0.5f, -0.5f},
//	{-0.5f, -0.5f, -0.5f},
//
//	{-0.5f, -0.5f, 0.5f},
//	{0.5f, -0.5f, 0.5f},
//	{0.5f, 0.5f, 0.5f},
//	{0.5f, 0.5f, 0.5f},
//	{-0.5f, 0.5f, 0.5f},
//	{-0.5f, -0.5f, 0.5f},
//
//	{-0.5f, 0.5f, 0.5f},
//	{-0.5f, 0.5f, -0.5f},
//	{-0.5f, -0.5f, -0.5f},
//	{-0.5f, -0.5f, -0.5f},
//	{-0.5f, -0.5f, 0.5f},
//	{-0.5f, 0.5f, 0.5f},
//
//	{0.5f, 0.5f, 0.5f},
//	{0.5f, 0.5f, -0.5f},
//	{0.5f, -0.5f, -0.5f},
//	{0.5f, -0.5f, -0.5f},
//	{0.5f, -0.5f, 0.5f},
//	{0.5f, 0.5f, 0.5f},
//
//	{-0.5f, -0.5f, -0.5f},
//	{0.5f, -0.5f, -0.5f},
//	{0.5f, -0.5f, 0.5f},
//	{0.5f, -0.5f, 0.5f},
//	{-0.5f, -0.5f, 0.5f},
//	{-0.5f, -0.5f, -0.5f},
//
//	{-0.5f, 0.5f, -0.5f},
//	{0.5f, 0.5f, -0.5f},
//	{0.5f, 0.5f, 0.5f},
//	{0.5f, 0.5f, 0.5f},
//	{-0.5f, 0.5f, 0.5f},
//	{-0.5f, 0.5f, -0.5f},
//};


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
	float rotateAngle = 0;

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

	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("error:glew初始化失败\n");
	}
	printf("OpenGL:%s\n", glGetString(GL_VERSION));
	//===============================================================================================

	GLuint VAO[1];
	GLuint VBO[1];
	GLuint texture;

	glGenVertexArrays(1, VAO);
	glBindVertexArray(VAO[0]);

	glGenBuffers(1, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);					//向Shader传入顶点坐标数据
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));	//向Shader传入顶点颜色数据
	glEnableVertexAttribArray(color);
	glVertexAttribPointer(textCoord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat))); //向Shader传入纹理坐标数据
	glEnableVertexAttribArray(textCoord);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);			//设置纹理的显示方式为重复显示
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		//放大的时候使用线性滤波方法让纹理看着更平滑
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  //缩小的时候为了节省资源和达到更好的效果，使用多级渐进纹理

	GLubyte *imageData = NULL;
	int imgWidth, imgHeight;
	imageData = SOIL_load_image("MyLoveTexture.png", &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);				//读取图片数据
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);	//定义纹理图像
	glGenerateMipmap(GL_TEXTURE_2D);
	//创建完纹理后图片资源就可以释放了
	SOIL_free_image_data(imageData);
	imageData = NULL;

	GLuint program = LoadShaders(cubeShaderInfo);
	
	glEnable(GL_DEPTH_TEST);  //无光照无贴图，暂时不用开启这两个功能
	//glEnable(GL_LIGHTING);
	glUseProgram(program);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		
		deltaTime = (GLfloat)glfwGetTime() - lastTime;
		lastTime = (GLfloat)glfwGetTime();
		rotateAngle += 20 * deltaTime;
		if (rotateAngle > 360)
			rotateAngle -= 360;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glBindVertexArray(VAO);
		

		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 model = glm::mat4(1);
		view[1][1];
		std::cout << glm::value_ptr(view);
		model = glm::rotate(model, glm::radians(rotateAngle), glm::vec3(0, 1, 0));
		view = glm::lookAt(camera.position, camera.position + camera.forward, camera.viewUp);
		projection = glm::perspective(glm::radians(70.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		

		GLuint modelLoc = glGetUniformLocation(program, "model");
		GLuint viewLoc = glGetUniformLocation(program, "view");
		GLuint projectionLoc = glGetUniformLocation(program, "projection");
		GLuint textureCoordLoc = glGetUniformLocation(program, "tex");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(textureCoordLoc, 0);
		

		glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture);
		

		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//glBindVertexArray(0);
		//glUseProgram(0);

		glfwSwapBuffers(window);
		
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}