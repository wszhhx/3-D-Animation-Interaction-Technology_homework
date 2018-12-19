#version 460 core
layout (location = 0) in vec3 vPosition;   
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertColor;
out vec2 textCoordination;


void main(){
	gl_Position = projection * view * vec4(vPosition,1.0);

	//����������ֱ�Ӵ���֮���ƬԪ��ɫ���ٽ��д���
	vertColor = color;
	textCoordination = textCoord;
}