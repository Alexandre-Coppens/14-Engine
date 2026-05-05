#version 450 core

layout(vertices = 3) out;

in VS_OUT{
   vec4 color;
   vec2 texCoord;
   vec3 normal;
} tesc_in[];

out TESC_OUT{
   vec4 color;
   vec2 texCoord;
   vec3 normal;
} tesc_out[];

uniform mat4 uViewProj;
uniform mat4 uWorldTransform;

void main(void)
{
   if (gl_InvocationID == 0)
   {
      const int MIN_TESS_LEVEL = 1;
      const int MAX_TESS_LEVEL = 60;
      const float MIN_DISTANCE = 0.1;
      const float MAX_DISTANCE = 100;
      
      vec4 eyeSpace0 = uViewProj * uWorldTransform * gl_in[0].gl_Position;
      vec4 eyeSpace1 = uViewProj * uWorldTransform * gl_in[1].gl_Position;
      vec4 eyeSpace2 = uViewProj * uWorldTransform * gl_in[2].gl_Position;
      
      float len0 = length(eyeSpace0.xyz);
      float len1 = length(eyeSpace1.xyz);
      float len2 = length(eyeSpace2.xyz);
      
      float distance0 = clamp((len0 - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE), 0.0, 1.0);
      float distance1 = clamp((len1 - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE), 0.0, 1.0);
      float distance2 = clamp((len2 - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE), 0.0, 1.0);
      
      float tessLevel0 = mix( MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance0, distance1));
      float tessLevel1 = mix( MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance1, distance2));
      float tessLevel2 = mix( MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance2, distance0));
      
      gl_TessLevelInner[0] = max(tessLevel0, tessLevel2);
      gl_TessLevelOuter[0] = tessLevel0;
      gl_TessLevelOuter[1] = tessLevel1;
      gl_TessLevelOuter[2] = tessLevel2;
   }
   gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
   tesc_out[gl_InvocationID].color = tesc_in[gl_InvocationID].color;
   tesc_out[gl_InvocationID].texCoord = tesc_in[gl_InvocationID].texCoord;
   tesc_out[gl_InvocationID].normal = tesc_in[gl_InvocationID].normal;
}
