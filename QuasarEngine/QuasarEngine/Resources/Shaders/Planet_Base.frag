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

   if(frag_in.perlinHeight <= 0.175) {
      color = vec3(0.239, 0.659, 0.639);
   } else if (frag_in.perlinHeight <= 0.250) {
      color = vec3(0.929, 0.882, 0.529);
   } else {
      color = mix(vec3(0.282, 0.459, 0.247), vec3(0.647, 0.659, 0.647), frag_in.perlinHeight);
   }

   FragColor = vec4(color, 1.0);
}