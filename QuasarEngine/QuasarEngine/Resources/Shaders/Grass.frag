#version 330

in vec2 fragTexCoord;
out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
   outColor = texture(uTexture, fragTexCoord * 2.0);
   outColor -= vec4(1.0) * (0.25 - fragTexCoord.y);
   //outColor = vec4(fragTexCoord.y, 0.0, 0.0, 1.0);
}
