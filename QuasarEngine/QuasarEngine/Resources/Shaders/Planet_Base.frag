#version 450 core

in TESE_OUT{
   vec4 color;
   vec2 texCoord;
} frag_in;

out vec4 FragColor;

void main()
{
   FragColor = vec4(frag_in.texCoord, 0.0, 1.0);
}