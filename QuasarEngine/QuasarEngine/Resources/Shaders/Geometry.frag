#version 330

in vec3 fragNormals;
out vec4 outColor;

void main()
{
   outColor = vec4(fragNormals, 1.0);
}
