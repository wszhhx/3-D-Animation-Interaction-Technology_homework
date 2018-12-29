#version 450 core

out vec4 fColor;

in vec3 fragNormal;
in vec3 fragPos;

smooth in vec2 textCoordination;

uniform sampler2D texSampler;

float ambientStrength = 0.2;

void main(){
	vec3 ambient = ambientStrength * vec3(1,1,1);
	vec3 backColor = vec3(texture2D(texSampler,textCoordination));
	fColor = vec4(backColor,1.0) * vec4(ambient,1.0);
}