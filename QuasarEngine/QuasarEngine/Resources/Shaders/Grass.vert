#version 450 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform sampler2D uTexture;
uniform float uTime;

out vec2 fragTexCoord;

float random (vec2 st) {
   return fract(sin(dot(st.xy,
                        vec2(12.9898,78.233))) * 43758.5453123);
}

vec3 rotateAroundZ(vec3 v, float r)
{
    return vec3( v.x * cos(r) - v.y * sin(r),
                 v.x * sin(r) + v.y * cos(r),
                 v.z);
}

void main()
{
    //Set Offset
    vec2 size = vec2(5.0, 5.0);
    vec4 offset = vec4((gl_InstanceID >> 10) - 512.0, (gl_InstanceID & 1023) - 512.0, 0.0, 0.0);
    
    //Add Random offset + Size it
    float randomX = random(vec2(gl_InstanceID, offset.x));
    float randomY = random(vec2(gl_InstanceID, randomX));
    offset.x = ((offset.x / 1024.0) + ( randomX - 0.5f)) * size.x;
    offset.y = ((offset.y / 1024.0) + ( randomY - 0.5f)) * size.y;

    //Add height
    float addedHeight = texture(uTexture, texCoord).r;
    offset.z = addedHeight * 0.1 * texCoord.y;
    
    //set grass age via texture coord
    vec2 newTexCoord = vec2(addedHeight, texCoord.y);
    
    //Rotate randomly around Z
    float randomRot = random(vec2(randomX, randomY));
    vec3 rotatedPos = vec3(rotateAroundZ(pos, (randomRot - 0.5) * 2));
    vec4 position = vec4(rotatedPos, 1.0) + offset;
    
    position.x += cos(uTime * 0.001) * texCoord.y * 0.01f;
    position.z -= cos(uTime * 0.001) * texCoord.y * 0.01f;

    gl_Position = position * uWorldTransform * uViewProj;
    fragTexCoord = newTexCoord;
}