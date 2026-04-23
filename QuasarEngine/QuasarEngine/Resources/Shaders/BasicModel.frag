#version 450

in vec2 fragTexCoord;
out vec4 outColor;

layout(binding = 0) uniform sampler2D uTexture;

void main()
{
   outColor = texture(uTexture, fragTexCoord);
}
