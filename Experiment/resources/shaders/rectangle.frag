#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform bool flipX;
uniform float alphaC; 

void main()
{
    vec2 flippedTexCoord = TexCoord;
    if (flipX) {
        flippedTexCoord.x = 1.0 - TexCoord.x; // Reverse the x-coordinate
    }
    FragColor = mix(texture(texture1, flippedTexCoord), texture(texture2, flippedTexCoord), alphaC);
}
