#version 450 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_texture; 

//uniform mat4 mvp;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 uv;
out vec3 pos;

void main() {
	//gl_Position = mvp * vec4(a_pos.xyz , 1.0);
    gl_Position =  modelMatrix * vec4(a_pos.xyz , 1.0);
	uv = a_texture;
	pos = a_pos;
}
