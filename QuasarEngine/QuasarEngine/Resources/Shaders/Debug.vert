#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform sampler2D uTexture;
uniform float uTime;

void main()
{
    gl_Position = vec4(pos + vec3(uTime * 0.01, 0.0, 0.0), 1.0) * uWorldTransform * uViewProj;
}