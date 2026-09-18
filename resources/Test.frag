#version 330 core

out vec4 outColor;

in vec3 normal;
in vec2 uv;

uniform sampler2D myTexture;

void main()
{
    vec3 textureColor = texture(myTexture, uv).rgb;
    outColor = vec4(textureColor, 1.0);
}