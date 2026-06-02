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
   float perlinHeight;
} tese_out;

uniform mat4 uViewProj;
uniform mat4 uWorldTransform;
uniform float uSphereRadius;
uniform float uNoiseStrength;
uniform float uNoiseSize;

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

vec3 hash( vec3 p ) // From: https://www.shadertoy.com/view/Xsl3Dl
{
   p = vec3( dot(p,vec3(127.1,311.7, 74.7)),
   dot(p,vec3(269.5,183.3,246.1)),
   dot(p,vec3(113.5,271.9,124.6)));

   return -1.0 + 2.0*fract(sin(p)*43758.5453123);
}

float noise( in vec3 p )
{
   vec3 i = floor( p );
   vec3 f = fract( p );
   
    // cubic interpolant
   vec3 u = f*f*(3.0-2.0*f);

   return mix( mix( mix( dot( hash( i + vec3(0.0,0.0,0.0) ), f - vec3(0.0,0.0,0.0) ),
                         dot( hash( i + vec3(1.0,0.0,0.0) ), f - vec3(1.0,0.0,0.0) ), u.x),
                    mix( dot( hash( i + vec3(0.0,1.0,0.0) ), f - vec3(0.0,1.0,0.0) ),
                         dot( hash( i + vec3(1.0,1.0,0.0) ), f - vec3(1.0,1.0,0.0) ), u.x), u.y),
               mix( mix( dot( hash( i + vec3(0.0,0.0,1.0) ), f - vec3(0.0,0.0,1.0) ),
                         dot( hash( i + vec3(1.0,0.0,1.0) ), f - vec3(1.0,0.0,1.0) ), u.x),
                    mix( dot( hash( i + vec3(0.0,1.0,1.0) ), f - vec3(0.0,1.0,1.0) ),
                         dot( hash( i + vec3(1.0,1.0,1.0) ), f - vec3(1.0,1.0,1.0) ), u.x), u.y), u.z );
}

void main(void)
{
   vec3 cubePos = (gl_TessCoord.x * gl_in[0].gl_Position.xyz +
   gl_TessCoord.y * gl_in[1].gl_Position.xyz +
   gl_TessCoord.z * gl_in[2].gl_Position.xyz);

   vec3 cubeSurface = cubePos / max(abs(cubePos.x), max(abs(cubePos.y), abs(cubePos.z)));

   vec3 spherePos = cubeToSphere(cubeSurface);
   float noise = clamp(noise(spherePos * uNoiseSize), 0.1, 1.0) ;
   vec3 sphereNoised = spherePos * uSphereRadius * (1 + noise * uNoiseStrength);
   gl_Position = vec4(sphereNoised, 1.0) * uWorldTransform * uViewProj;
   
   tese_out.color = mix(tese_in[0].color, tese_in[1].color, gl_TessCoord.x);
   tese_out.texCoord = interpolate2D(tese_in[0].texCoord, tese_in[1].texCoord, tese_in[2].texCoord);
   tese_out.perlinHeight = noise;
}