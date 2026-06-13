#version 330

out vec4 outColor;

uniform sampler2D uTexture;
uniform float uTime;

void main()
{
      outColor = vec4(0.5, 0.5, 0.5, 1.0);
}
