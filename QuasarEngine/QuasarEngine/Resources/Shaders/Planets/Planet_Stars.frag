#version 330

in float temperature;
in float speed;
out vec4 outColor;

uniform sampler2D uTexture;
uniform float uTime;

void main()
{ 
      outColor = texture(uTexture, vec2(sin(uTime * speed), temperature));
}
