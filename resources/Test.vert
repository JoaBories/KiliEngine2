#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vUv;

out vec2 uv;

uniform float uTime;
uniform mat4 uTransform;
uniform mat4 uViewProjMatrix;

void main()
{
    float speed = 0.5;
    
    gl_Position = vec4(vPos, 1.0) * uTransform * uViewProjMatrix;
    
    uv = vUv;
}