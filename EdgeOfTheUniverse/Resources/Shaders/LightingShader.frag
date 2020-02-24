#version 330 core
in vec2 CoordsUV;
out vec4 color;

uniform vec4 Color;

uniform sampler2D textureSampler;

uniform vec4 textureCoords;

vec2 coords;

void main()
{

	coords = vec2(CoordsUV.x * textureCoords.z + textureCoords.x, CoordsUV.y * textureCoords.w + textureCoords.y);
	vec4 tColor = texture(textureSampler, coords) * Color;



	color = tColor;
}