#pragma once

#include "PublicData.h"

GLfloat lastTime = 0;
GLfloat deltaTime = 0.1;
GLuint program = 0;
SphereGenerator planetEntities[10];

ShaderInfo planetShaders[] = {
   {GL_VERTEX_SHADER,"PlanetVertexShader.vert",0},
   {GL_FRAGMENT_SHADER,"PlanetFragmentShader.frag",0},
	{GL_NONE,"xxx",0}
};
