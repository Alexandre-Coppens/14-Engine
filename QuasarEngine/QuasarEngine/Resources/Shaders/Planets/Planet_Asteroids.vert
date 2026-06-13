#version 450 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform float uTime;

uniform float uSpeed;
uniform float uUpSize;
uniform float uInteriorRingDist;
uniform float uExteriorRingDist;

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233))) * 43758.5453123);
}

void main()
{
    const float PI = 3.14159265359;

    float angleSeed  = smoothstep( 0, 1, random(vec2(gl_InstanceID, uUpSize)));
    float radiusSeed = random(vec2(gl_InstanceID + 1000.0, uUpSize));
    float heightSeed = smoothstep( 0, 1, random(vec2(gl_InstanceID + 2000.0, uUpSize)));

    float theta = angleSeed * PI * 2 + uTime * uSpeed;
    float finalRadius = sqrt((1.0 - radiusSeed) * uInteriorRingDist * uInteriorRingDist + radiusSeed * uExteriorRingDist * uExteriorRingDist);

    vec2 ringOffset = vec2(cos(theta), sin(theta)) * finalRadius;
    float zOffset = (heightSeed - 0.5) * 2.0 * uUpSize;

    vec4 position = vec4(pos + vec3(ringOffset, zOffset), 1.0);
    gl_Position = position * uWorldTransform * uViewProj;
}