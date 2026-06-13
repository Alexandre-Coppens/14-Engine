#version 450 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform float uTime;

uniform float uDistanceRadius;
uniform float uMeshInvScale;

out float temperature;
out float speed;

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233))) * 43758.5453123);
}

void main()
{
    float x = random(vec2(gl_InstanceID, uDistanceRadius));
    float y = random(vec2(gl_InstanceID, x));
    float z = random(vec2(uDistanceRadius, y));
    
    vec3 normal = (vec3(x, y, z) - vec3(0.5)) * 2.0;
    vec4 position = vec4(pos + normal * uDistanceRadius * uMeshInvScale, 1.0);
    
    gl_Position = position * uWorldTransform * uViewProj;
    temperature = (x + y + z) * 0.333;
    speed = mix(0.005, 0.001, y);
}