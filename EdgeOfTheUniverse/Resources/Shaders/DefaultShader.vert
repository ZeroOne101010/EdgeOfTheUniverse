#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 coordsUV;

uniform int optimizeMode;
uniform vec2 localPos;
uniform vec2 worldPos;
uniform vec2 relSize;
uniform vec2 correctSize;
uniform vec2 size;

uniform float angle;

out vec2 CoordsUV;

void main() 
{
	//gl_Position = vec4(worldPos, 0.0) + (  vec4(relSize, 1.0) * vec4(size, 1.0) * vec4(correctSize, 1.0) * ( (rotation * vec4(position, 1.0))) ) + vec4(correctSize, 1.0) * (rotation * vec4(localPos, 0.0));
	//gl_Position = vec4(correctSize, 1.0) * vec4(worldPos, 0.0) + (  vec4(relSize, 1.0) * vec4(size, 1.0) * vec4(correctSize, 1.0) * ( (vec4(position, 1.0) * rotation)) ) + vec4(correctSize, 1.0) * (vec4(localPos, 0.0) * rotation);
	//vec2 p = vec2(correctSize.xy) * vec2(worldPos.xy) + (  vec2(relSize.xy) * vec2(size.xy) * vec2(correctSize.xy) * ( (    vec2(position.x * cos(angle), position.y * sin(angle))      )) ) + vec2(correctSize.xy) * (vec2(localPos.x * cos(angle), localPos.y * sin(angle)));
	
//		float v0 = -3.14 / 2;
//		vec2 v = vec2(position.x * sin(angle + v0 ) + position.y * cos(angle + v0), position.x * cos(angle + v0) - position.y * sin(angle + v0));
//		vec2 v1 = vec2(localPos.x * sin(angle + v0) + localPos.y * cos(angle + v0), localPos.x * cos(angle + v0) - localPos.y * sin(angle + v0));
//		vec2 p = vec2(correctSize.xy) * vec2(worldPos.xy) + (  vec2(relSize.xy) * vec2(size.xy) * vec2(correctSize.xy) * ( (  v   )) ) + vec2(correctSize.xy) * (  v1  );
 
//		vec2 v = vec2(position.x * cos(angle) + position.y * sin(angle), position.y * cos(angle) - position.x * sin(angle));
//		vec2 v1 = vec2(localPos.x * cos(angle) + localPos.y * sin(angle), localPos.y * cos(angle) - localPos.x * sin(angle));
//		vec2 p = vec2(correctSize.xy) * vec2(worldPos.xy) + (  vec2(relSize.xy) * vec2(size.xy) * vec2(correctSize.xy) * ( (  v   )) ) + vec2(correctSize.xy) * (  v1  );
//		gl_Position = vec4(p, 0, 1);
		
		vec2 p = vec2(0, 0);

		if(optimizeMode == 0)
		{
		float s = sin(angle);
		float c = cos(angle);

		p = correctSize * worldPos + (  relSize * size * correctSize * ( (  vec2(position.x * c + position.y * s, position.y * c - position.x * s)   )) ) + correctSize * (  vec2(localPos.x * c + localPos.y * s, localPos.y * c - localPos.x * s)  );
		}
		else
		{
		p = correctSize * (worldPos +  size *  position.xy);
		}
		gl_Position = vec4(p, 0, 1);
	
	CoordsUV = coordsUV;
}