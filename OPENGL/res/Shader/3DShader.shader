#shader sid_vertex
#version 330 core
layout(location = 0) in vec3 position;

out vec4 vCol;

uniform mat4 u_MVP;


void main()
{
	gl_Position = u_MVP * vec4(position, 1.0f);
	vCol = vec4(clamp(position, 0.0f, 1.0f), 1.0f);
}


#shader sid_fragment

#version 330 core

layout(location = 0) out vec4 color;

in vec4 vCol;
uniform vec4 u_color; // idna naavu fragment shader du main nalli use maadtilla sadhyakke noodko

void main()
{
	color = vCol;
}