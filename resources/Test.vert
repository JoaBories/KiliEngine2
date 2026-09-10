#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 vColor;

out vec4 color; 

void main()
{
    gl_Position = vec4(pos, 1.0);
    color = vColor;
}