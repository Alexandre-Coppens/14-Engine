#version 450 core

layout(triangles, fractional_even_spacing, cw) in;

in TESC_OUT{
   vec4 color;
   vec2 texCoord;
   vec3 normal;
} tese_in[];

out TESE_OUT{
   vec4 color;
   vec2 texCoord;
   vec3 normal;
} tese_out;

uniform mat4 uViewProj;
uniform mat4 uWorldTransform;
uniform float uSphereRadius;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
   return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 cubeToSphere(vec3 cubePos)
{
   float cX = cubePos.x * cubePos.x;
   float cY = cubePos.y * cubePos.y;
   float cZ = cubePos.z * cubePos.z;
   
   float pX = cX * 0.5;
   float pY = cY * 0.5;
   float pZ = cZ * 0.5;
   
   float x = cubePos.x * sqrt( 1 - pY - pZ + (cY * cZ) / 3);
   float y = cubePos.y * sqrt( 1 - pZ - pX + (cZ * cX) / 3);
   float z = cubePos.z * sqrt( 1 - pX - pY + (cX * cY) / 3);

   return vec3(x, y, z);
}

void main(void)
{
   vec3 cubePos = (gl_TessCoord.x * gl_in[0].gl_Position.xyz +
   gl_TessCoord.y * gl_in[1].gl_Position.xyz +
   gl_TessCoord.z * gl_in[2].gl_Position.xyz);

   vec3 cubeSurface = cubePos / max(abs(cubePos.x), max(abs(cubePos.y), abs(cubePos.z)));

   vec3 spherePos = cubeToSphere(cubeSurface) * uSphereRadius * 0.5;
   gl_Position = vec4(spherePos, 1.0) * uWorldTransform * uViewProj;
   
   tese_out.color = mix(tese_in[0].color, tese_in[1].color, gl_TessCoord.x);
   tese_out.texCoord = interpolate2D(tese_in[0].texCoord, tese_in[1].texCoord, tese_in[2].texCoord);
}