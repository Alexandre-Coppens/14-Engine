#version 330

in vec2 fragTexCoord;
out vec4 outColor;

uniform sampler2D uNULLTexture;

void main()
{
   outColor = texture(uTexture, fragTexCoord);
}
