#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUv;

out vec3 normal;
out vec2 uv;

uniform float uTime;
uniform mat4 uTransform;
uniform mat4 uViewProjMatrix;

void main()
{
    float speed = 0.5;
    
    gl_Position = vec4(vPos, 1.0) * uTransform * uViewProjMatrix;
    
    normal = (vec4(vNormal, 0.0) * uTransform).xyz;
    uv = vUv;
}