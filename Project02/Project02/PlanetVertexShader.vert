#version 450 core
layout (location = 0) in vec3 vPosition;   
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textCoord;

out vec2 textCoordination;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){

	gl_Position = projection * view * model * vec4(vPosition, 1.0);

	textCoordination = textCoord;
}