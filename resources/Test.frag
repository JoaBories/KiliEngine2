#version 330 core

out vec4 outColor;

in vec3 normal;
in vec2 uv;

void main()
{
    outColor = vec4(normal, 1.0f);
}