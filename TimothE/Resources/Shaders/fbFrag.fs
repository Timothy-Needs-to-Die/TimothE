#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform bool shouldBeBlack;
uniform float blackAlpha;
uniform bool fadingIn;

void main()
{
    
    vec3 col;

    col = shouldBeBlack ? vec3(0.0) : texture(screenTexture, TexCoords).rgb;

    if(fadingIn){
        float r = mix(col.r, 0.0, blackAlpha);
        float g = mix(col.g, 0.0, blackAlpha);
        float b = mix(col.b, 0.0, blackAlpha);
        FragColor = vec4(r,g,b,1.0);

    }
    else
    {
        FragColor = vec4(col, 1.0);
    }

} 