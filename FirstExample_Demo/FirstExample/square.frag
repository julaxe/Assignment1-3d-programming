#version 430 core

in vec3 color;
out vec4 frag_color;

uniform vec4 u_Color;

void main()
{
	frag_color = u_Color;
}