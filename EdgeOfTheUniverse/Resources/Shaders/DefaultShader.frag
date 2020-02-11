#version 330 core
in vec2 CoordsUV;
out vec4 color;

uniform vec4 Color;

uniform float v[300];
uniform sampler2D textureSampler;

void main()
{
	vec4 tColor = texture(textureSampler, CoordsUV) * Color;
//	if(tColor.w < 1)
//	{
//	tColor = vec4(1, 0, 0, 1);
//	}
	//color = texture(textureSampler, CoordsUV);
	color = tColor;
}