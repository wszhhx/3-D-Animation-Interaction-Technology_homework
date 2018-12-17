#include<cstdlib>
#include<iostream>

#include<GL/glew.h>

#include "MyShaderLoader.h"

const GLchar* ReadShader(const char *filename) {
	FILE *shaderFile;
	fopen_s(&shaderFile, filename, "rb");

	if (shaderFile == NULL) {
		std::cerr << "error:�޷�����ɫ�������ļ�" << std::endl;
		return NULL;
	}

	fseek(shaderFile, 0L, SEEK_END);
	int fileLength = ftell(shaderFile);
	fseek(shaderFile, 0L, SEEK_SET);

	GLchar *source = new GLchar[fileLength + 1];

	fread(source, 1, fileLength, shaderFile);
	fclose(shaderFile);

	source[fileLength] = 0;

	return const_cast<const GLchar *>(source);
}

GLuint LoadShaders(ShaderInfo *shaders) {
	if (shaders == NULL) {
		printf("error:ShaderInfo������\n");
		return 0;
	}

	GLuint program = glCreateProgram();
	GLuint shader;

	ShaderInfo *currentShaderInfo = shaders;
	while (currentShaderInfo->type != GL_NONE) {
		std::cout << "==================================================================" << std::endl;
		std::cout << "log:��ʼװ����ɫ����";
		switch (currentShaderInfo->type)
		{
		case GL_VERTEX_SHADER:
			std::cout << "������ɫ��" << std::endl;
			break;
		case GL_FRAGMENT_SHADER:
			std::cout << "ƬԪ��ɫ��" << std::endl;
			break;
		default:
			std::cout << "δ֪��ɫ������" << std::endl;
			break;
		}
		

		shader = glCreateShader(currentShaderInfo->type);
		currentShaderInfo->shader = shader;
		const GLchar *shaderSourceCode = ReadShader(currentShaderInfo->filename);

		if (shaderSourceCode == NULL) {		//ֻҪһ����ɫ�������Ҫж��������ɫ���˳�����
			for (currentShaderInfo = shaders; currentShaderInfo != NULL; ++currentShaderInfo) {
				glDeleteShader(currentShaderInfo->shader);
				currentShaderInfo->shader = 0;
			}
			return 0;
		}

		glShaderSource(shader, 1, &shaderSourceCode, NULL);
		delete[] shaderSourceCode;

		glCompileShader(shader);

		GLint isCompiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (!isCompiled) {
			GLsizei logLen;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);

			GLchar *log = new GLchar[logLen + 1];
			glGetShaderInfoLog(shader, logLen, &logLen, log);

			std::cerr << "error:�������" << std::endl;
			std::cerr << log << std::endl << std::endl;
			
			delete[] log;
			
			return 0;
		}

		glAttachShader(program, shader);
		std::cout << "log:װ����ϣ�" << std::endl << std::endl;
		++currentShaderInfo;
	}

	glLinkProgram(program);

	GLint isLinked;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

	if (!isLinked) {
		GLsizei logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

		GLchar *log = new GLchar[logLength + 1];
		glGetProgramInfoLog(program, logLength, &logLength, log);
		std::cout << "==================================================================" << std::endl;
		std::cerr << "error:��ɫ���������Ӵ���" << std::endl;
		
		delete[] log;

		for (currentShaderInfo = shaders; currentShaderInfo != NULL; ++currentShaderInfo) {
			glDeleteShader(currentShaderInfo->shader);
			currentShaderInfo->shader = 0;
		}
		return 0;
	}

	return program;
}




