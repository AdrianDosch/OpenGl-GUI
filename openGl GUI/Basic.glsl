#shader vertex
#version 440 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 col;

out vec4 t_color;

uniform mat4 MVP;

void main()
{
	t_color = col;
   gl_Position = MVP * position;
};



#shader fragment
#version 440 core

layout(location = 0) out vec4 color;

in vec4 t_color;

void main()
{
	color = t_color;
};