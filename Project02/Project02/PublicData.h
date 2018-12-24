#pragma once
#include "MyShaderLoader.h"
#include "SphereGenerator.h"

enum { sun = 0, mercury };
enum { vPosition = 0, color, textCoord };

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 1024;
const int DAY_PER_SECOND = 5;


extern SphereGenerator planetEntities[];

extern GLfloat lastTime;
extern GLfloat deltaTime;
extern GLuint program;



extern ShaderInfo planetShaders[];

