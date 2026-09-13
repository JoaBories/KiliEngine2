#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 vColor;

out vec4 color; 

uniform float uTime;

void main()
{
    float speed = 0.5f;
    
    float c = cos(uTime * speed);
    float s = sin(uTime * speed);

    vec2 rotatedPosition;
    rotatedPosition.x = (c * pos.x) - (s * pos.y);
    rotatedPosition.y = (s * pos.x) + (c * pos.y);
    
    gl_Position = vec4(rotatedPosition, 0.0, 1.0);
    color = vColor;
}