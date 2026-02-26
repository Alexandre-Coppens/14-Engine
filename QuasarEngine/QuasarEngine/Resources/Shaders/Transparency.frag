#version 330 core

in vec2 fragTexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    vec4 color = texture(uTexture, TexCoords);
    if(color.a < 0.25)
    discard;
    FragColor = color;
}