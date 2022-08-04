#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform bool shouldBeBlack;

void main()
{
    
    vec3 col;

    col = shouldBeBlack ? vec3(0.0) : texture(screenTexture, TexCoords).rgb;

    FragColor = vec4(col, 1.0);
} 