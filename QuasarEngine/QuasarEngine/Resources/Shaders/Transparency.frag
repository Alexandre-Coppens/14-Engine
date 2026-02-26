#version 330 core

in vec3 fragNormals;
in vec2 fragTexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    vec4 color = texture(uTexture, fragTexCoord);
    if(color.a < 0.25)
    discard;
    FragColor = color;
}