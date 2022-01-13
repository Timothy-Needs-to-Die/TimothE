#version 330 core

layout(location = 0) in vec4 position;
out gl_position;

void main()
{
    gl_position = position;
}