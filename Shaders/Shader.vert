#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 inTex;

out vec2 TexCoord;
void main()
{
gl_Position = vec4(-pos.x, -pos.y, 0.0,1.0);
TexCoord.x = 1.0-inTex.x;
TexCoord.y = inTex.y;
}
