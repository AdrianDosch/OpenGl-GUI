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

layout(location = 0) out vec4 color;

in vec4 t_color;

void main()
{
	color = vec4(1.f, 1.f, 1.f, 1.f);
};