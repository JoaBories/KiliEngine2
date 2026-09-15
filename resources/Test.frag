#version 330 core

out vec4 outColor;

in vec4 color;
in vec2 uv;

void main()
{
    outColor = vec4(color);
}