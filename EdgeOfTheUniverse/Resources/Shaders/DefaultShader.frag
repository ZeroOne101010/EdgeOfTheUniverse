#version 330 core
out vec4 color;

uniform vec4 Color;

uniform float v[300];

void main()
{
	color = Color;
}