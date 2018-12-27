#version 450 core

out vec4 fColor;
smooth in vec2 textCoordination;

uniform sampler2D texSampler;

float ambientStrength = 0.2;

void main(){
	vec3 ambient = ambientStrength * vec3(1,1,1);

	fColor = texture2D(texSampler,textCoordination);
}