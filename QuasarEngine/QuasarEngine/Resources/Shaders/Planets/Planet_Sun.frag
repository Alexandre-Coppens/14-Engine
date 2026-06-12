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

   if(frag_in.perlinHeight <= -0.1) {
      color = vec3(0.500, 0.015, 0.015);
   } else if(frag_in.perlinHeight <= 0.033) {
      color = vec3(0.761, 0.039, 0.039);
   } else if (frag_in.perlinHeight <= 0.115) {
      color = vec3(0.941, 0.294, 0.035);
   } else if (frag_in.perlinHeight <= 0.200) {
      color = vec3(0.836, 0.428, 0.048);
   } else if (frag_in.perlinHeight <= 0.240) {
      color = vec3(0.960, 0.864, 0.116);
   } else {
      color = mix(vec3(0.960, 0.816, 0.576), vec3(0.932, 0.900, 0.832), frag_in.perlinHeight);
   }

   FragColor = vec4(color, 1.0);
}