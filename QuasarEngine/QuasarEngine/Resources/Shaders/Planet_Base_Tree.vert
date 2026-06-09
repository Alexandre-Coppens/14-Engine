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
uniform float uSphereRadius;
uniform float uNoiseStrength;
uniform float uNoiseSize;

out vec2 fragTexCoord;

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233))) * 43758.5453123);
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

void main()
{
    const float PI = 3.14159265359;
    
    float longitude = floor(gl_InstanceID / float(uLatNumber)) + random(vec2(gl_InstanceID));
    float latitude = float(gl_InstanceID % uLatNumber) + random(vec2(gl_InstanceID, longitude));
    
    float latAngle = ((float(latitude) + 0.5 ) / float(uLatNumber)) * PI;
    float longAngle = ((float(longitude) + 0.5) / float(uLongNumber)) * 2.0 * PI;
    
    vec3 normal = vec3(
       sin(latAngle) * cos(longAngle),
       sin(latAngle) * sin(longAngle),
       cos(latAngle)                  
    );
    
    vec3 up = abs(normal.y) < 0.999 ? vec3(0.0, 1.0, 0.0) : vec3(1.0, 0.0, 0.0);
    vec3 T = normalize(cross(up, normal));
    vec3 B = cross(normal, T);
    
    vec3 rotatedPos = T * pos.x + B * pos.y + normal * pos.z;
    
    float noise = clamp(noise(normal * uNoiseSize), 0.1, 1.0) ;
    vec3 sphereNoised = rotatedPos + normal * uSphereRadius * 10 * (1 + noise * uNoiseStrength);
    
    vec4 position = vec4(sphereNoised, 1.0);
    
    if(noise <= 0.175) position = vec4(0.0, 0.0, 0.0, 1.0);
    
    gl_Position = position * uWorldTransform * uViewProj;
    fragTexCoord = texCoord;
}