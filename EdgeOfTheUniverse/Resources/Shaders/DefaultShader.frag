#version 330 core
in vec2 CoordsUV;
out vec4 color;

uniform vec4 Color;

uniform float v[300];
uniform sampler2D textureSampler;
 vec2 coords;

void main()
{
	coords = vec2(CoordsUV.x * 2, CoordsUV.y * 2);
	vec4 tColor = texture(textureSampler, coords) * Color;
//	if(tColor.w < 1)
//	{
//	tColor = vec4(1, 0, 0, 1);
//	}
	//color = texture(textureSampler, CoordsUV);
	color = tColor;
}