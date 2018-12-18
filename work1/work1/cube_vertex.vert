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
	//gl_Position = projection * view * model * vec4(vPosition,1.0);	//֮������Щ�任֮��ͼ����Ⱦ��������ԭ������Щ�任����Ⱦ����Ʒ�����ü������ˡ�
	//gl_Position = test * vec4(vPosition,1.0);
	gl_Position = projection * view * vec4(vPosition,1.0);
}