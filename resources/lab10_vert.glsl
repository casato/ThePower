#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec4 Pcolor;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

out vec4 partCol;


void main()
{
	gl_Position = P * V * M * vec4(vertPos.xyz, 1.0);

	partCol = Pcolor;
}
