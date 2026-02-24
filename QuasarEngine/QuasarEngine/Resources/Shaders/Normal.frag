#version 330 core

in vec3 fragNormals;
out vec4 color;

void main()
{
    color = vec4(fragNormals, 1.0);
}