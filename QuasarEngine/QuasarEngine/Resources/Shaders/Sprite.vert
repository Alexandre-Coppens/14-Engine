#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoord;

uniform vec2 uLocation;

out vec2 fragTexCoord;

void main()
{
    gl_Position = vec4(pos + vec3(uLocation.x, 0.0f, uLocation.y), 1.0);
    fragTexCoord = texCoord;
}