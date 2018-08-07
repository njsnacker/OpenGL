#version 450 core
layout (location = 0) in vec3 a_pos;
//layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texture;
layout (location = 3) in vec3 a_offset;

//uniform mat4 mvp;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 uv;
out vec3 pos;

void main() {
	//gl_Position = mvp * vec4(a_pos.xyz , 1.0);
	//vec3 offset = a_offset[gl_InstanceID];
    //gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(a_pos.xyz + a_offset , 1.0);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(a_pos.xyz, 1.0);
	uv = a_texture;
	pos = a_pos;
}
