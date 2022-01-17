#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 transform;
void main()
{
    gl_Position = transform * position;
    TexCoord = texCoord;
}