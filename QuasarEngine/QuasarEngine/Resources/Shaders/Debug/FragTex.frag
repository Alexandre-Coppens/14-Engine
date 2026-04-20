#version 330

in vec2 fragTexCoord;
out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
    outColor = vec4(fragTexCoord.xy, 0.0f, 1.0f);
}
