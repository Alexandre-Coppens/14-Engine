#version 450 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform sampler2D uTexture;
uniform float uTime;

uniform int uLongNumber;
uniform int uLatNumber;
uniform float uRadius;

out vec2 fragTexCoord;

void main()
{
   const float PI = 3.14159265359;

   float longitude = floor(gl_InstanceID / float(uLatNumber));
   float latitude = float(gl_InstanceID % uLatNumber);

   float latAngle = ((float(latitude) + 0.5 ) / float(uLatNumber)) * PI;
   float longAngle = ((float(longitude) + 0.5) / float(uLongNumber)) * 2.0 * PI;

   vec4 offset = vec4(
      (sin(latAngle) * cos(longAngle)),
      cos(latAngle),
      sin(latAngle) * sin(longAngle),
      0.0
   );
    
    vec4 sphereOffset = offset * uRadius;
    vec4 position = vec4(pos, 1.0) + sphereOffset;

    gl_Position = position * uWorldTransform * uViewProj;
    fragTexCoord = texCoord;
}