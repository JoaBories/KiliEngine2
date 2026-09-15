#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec2 vUv;

out vec4 color; 
out vec2 uv;

uniform float uTime;

void main()
{
    float speed = 0.5f;
    
    float c = cos(uTime * speed);
    float s = sin(uTime * speed);

    vec2 rotatedPosition;
    rotatedPosition.x = (c * vPos.x) - (s * vPos.y);
    rotatedPosition.y = (s * vPos.x) + (c * vPos.y);
    
    gl_Position = vec4(rotatedPosition, 0.0, 1.0);
    
    color = vColor;
    uv = vUv;
}