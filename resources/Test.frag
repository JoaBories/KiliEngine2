#version 330 core

out vec4 outColor;

in vec2 uv;

void main()
{
    outColor = vec4(uv, 0.0f, 1.0f);
}