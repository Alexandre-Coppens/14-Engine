#version 450 core

layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

in VS_OUT{
   vec3 normal;
} gs_in[];

out vec3 fragNormals;

void main() {
   vec4 centerPos = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0f;
   vec4 centerNormal = vec4((gs_in[0].normal + gs_in[1].normal + gs_in[2].normal)/3.0f, 0.0f);
   centerNormal = centerNormal.xzyw;
   gl_Position = centerPos;
   fragNormals = centerNormal.xyz;
   EmitVertex();
   gl_Position = centerPos + centerNormal * 0.3f * uWorldTransform * uViewProj;
   fragNormals = centerNormal.xyz;
   EmitVertex();
   EndPrimitive();
}
