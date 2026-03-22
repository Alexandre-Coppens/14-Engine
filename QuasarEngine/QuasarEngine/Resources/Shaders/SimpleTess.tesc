#version 330 core

layout(vertices = 3) out;

in VS_OUT{
   vec4 color;
   vec2 texCoord;
} tesc_in[];
out TESC_OUT{
   vec4 color;
   vec2 texCoord;
}tesc_out[];

void main()
{
   if(gl_InvocationID == 0)
   {
      gl_TessLevelInner[0] = 5.0f;
      gl_TessLevelOuter[0] = 5.0f;
      gl_TessLevelOuter[1] = 5.0f;
      gl_TessLevelOuter[2] = 5.0f;
   }
   gl_out[gl_invocationid].gl_Position = gl_in[gl_InvocationID].gl_Position;
   tesc_out[gl_invocationid].color = tesc_in[gl_invocationid].color;
   tesc_out[gl_invocationid].texCoord = tesc_in[gl_invocationid].texCoord;
}