#shader sid_vertex
#version 400 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;

out vec2 v_TexCoord;    // idu the most important, vec2 ***v_TexCoord*** , eee irbeku
						// make sure you know the language of the shader
						// Goooodddd maannnnnnnnnnnnnn this gave me a hard time for two days
uniform mat4 u_MVP;


void main()
{
	gl_Position = u_MVP * position; // gl_Position is also a inbuilt one so don't make any mitake in that too
	v_TexCoord = texcoord;
}


#shader sid_fragment

#version 400 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_color; // idna naavu fragment shader du main nalli use maadtilla sadhyakke noodko
uniform sampler2D u_texture; // for this time the u_ can be anything but v_ should be the same as the syntax

void main()
{
	vec4 texColor = texture(u_texture, v_TexCoord);
	color = texColor * u_color;
}