#version 460 core
layout (location = 0) in vec3 vPosition;   

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
mat4 test = mat4(1.0,0.0,0.0,0.0,
				 0.0,1.0,0.0,0.0,
				 0.0,0.0,1.0,0.0,
				 0.0,0.0,0.0,1.0);

void main(){
	//gl_Position = projection * view * model * vec4(vPosition,1.0);	//之所以这些变换之后图形渲染不出来的原因是这些变换让渲染的物品超出裁剪区域了。
	//gl_Position = test * vec4(vPosition,1.0);
	gl_Position = projection * view * vec4(vPosition,1.0);
}