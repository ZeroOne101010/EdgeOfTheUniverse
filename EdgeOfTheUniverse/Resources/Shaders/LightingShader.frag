#version 330 core
in vec2 CoordsUV;
out vec4 color;

uniform vec4 Color;

uniform float v[300];
uniform sampler2D textureSampler;
uniform vec4 textureCoords;

uniform vec2 sizeBuffer;
uniform int positionBlockInBuffer;
uniform vec3 blockBrightnessBuffer[];

vec2 coords;

void main()
{
	coords = vec2(CoordsUV.x * textureCoords.z + textureCoords.x, CoordsUV.y * textureCoords.w + textureCoords.y);
	vec4 tColor = texture(textureSampler, coords) * Color;



	color = tColor;
}