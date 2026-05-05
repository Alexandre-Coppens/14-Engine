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
} tese_out;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform sampler2D uTexture;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

void main(void)
{
    tese_out.color = mix(tese_in[0].color, tese_in[1].color, gl_TessCoord.x);
    tese_out.texCoord = interpolate2D(tese_in[0].texCoord, tese_in[1].texCoord, tese_in[2].texCoord);
    
    vec4 heightMap = texture(uTexture, tese_out.texCoord);
    vec4 addedHeight = vec4(tese_in[0].normal * (heightMap.x * 0.2), 0.0);
    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +
    gl_TessCoord.y * gl_in[1].gl_Position +
    gl_TessCoord.z * gl_in[2].gl_Position);
    gl_Position += addedHeight;
}