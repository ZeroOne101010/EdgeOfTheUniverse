#version 330 core
layout (location = 0) in vec3 position;

uniform vec3 localPos;
uniform vec3 worldPos;

uniform mat4 rotation;

//uniform mat4 localPos;
//uniform mat4 worldPos;

void main() 
{
	gl_Position = vec4(worldPos, 0) + vec4(localPos, 0) + rotation * vec4(position, 1.0);
	//gl_Position = vec4(position, 1.0);
	//gl_Position = worldPos * localPos * vec4(position, 1.0);
}