#shader vertex
#version 440 core

layout(location = 0) in vec4 position;

uniform mat4 MVP;

void main()
{
   gl_Position = MVP * position;
};



#shader fragment
#version 440 core
out vec4 color;

uniform vec2 radius;
uniform vec2 ofset;
uniform vec2 windowSize;

void main()
{
	float xPos =  pow((gl_FragCoord / windowSize.y - ofset.x).x, 2);
	float yPos =  pow((gl_FragCoord / windowSize.y - ofset.y).y, 2);

	if(xPos + yPos <= pow(radius.x, 2))
		color = vec4(0.4f, 0.1f, 0.9f, 1.f);
	else
		discard;
}