#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 coordsUV;

uniform vec3 localPos;
uniform vec3 worldPos;
uniform vec3 relSize;
uniform vec3 correctSize;
uniform vec3 size;

uniform mat4 rotation;

out vec2 CoordsUV;

void main() 
{
	//gl_Position = vec4(worldPos, 0.0) + (  vec4(relSize, 1.0) * vec4(size, 1.0) * vec4(correctSize, 1.0) * ( (rotation * vec4(position, 1.0))) ) + vec4(correctSize, 1.0) * (rotation * vec4(localPos, 0.0));
	gl_Position = vec4(correctSize, 1.0) * vec4(worldPos, 0.0) + (  vec4(relSize, 1.0) * vec4(size, 1.0) * vec4(correctSize, 1.0) * ( (vec4(position, 1.0) * rotation)) ) + vec4(correctSize, 1.0) * (vec4(localPos, 0.0) * rotation);
	//gl_Position = vec4(worldPos, 0.0) + (  vec4(relSize, 1.0) * vec4(size, 1.0) * vec4(correctSize, 1.0) * ( (vec4(position, 1.0))) );
	CoordsUV = coordsUV;
}