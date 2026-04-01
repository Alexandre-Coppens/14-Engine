#version 450 core

in vec3 pos;
in vec3 normal;
in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

out VS_OUT{
   vec3 normal;
} vs_out;

void main()
{
   gl_Position = vec4(pos, 1.0) * uWorldTransform * uViewProj;
   vs_out.normal = normal;
}
