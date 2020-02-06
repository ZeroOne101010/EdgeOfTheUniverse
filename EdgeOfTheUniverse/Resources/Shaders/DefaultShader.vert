#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 localPos;
uniform mat4 worldPos;

void main() 
{
	gl_Position = worldPos * localPos * vec4(position, 1.0);
}