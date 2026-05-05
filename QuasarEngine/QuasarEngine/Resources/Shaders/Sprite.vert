#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoord;

uniform vec2 uLocation;
uniform vec2 uScale;
uniform mat4 uViewProj;

out vec2 fragTexCoord;

void main()
{
    vec2 worldLocation = pos.xy * uScale + uLocation ;
    gl_Position = vec4(worldLocation, pos.z, 1.0) * uViewProj;
    fragTexCoord = texCoord.yx;
}