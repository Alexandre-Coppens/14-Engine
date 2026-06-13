#version 450 core

in TESE_OUT{
   vec4 color;
   vec2 texCoord;
   vec3 normal;
   float perlinHeight;
} frag_in;

out vec4 FragColor;

void main()
{
   vec3 color;
   
   color = mix(vec3(0.466, 0.360, 0.588) * 0.5, vec3(0.360, 0.572, 0.588), clamp(frag_in.perlinHeight - 0.25, 0, 1));

   FragColor = vec4(color, 1.0);
}