#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 inTex;
out vec4 colour2;
uniform vec2 mouse;
out vec2 TexCoord;
uniform mat4 model;
uniform mat4 projection;
void main()
{
colour2 = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
gl_Position = projection * model * vec4(pos.x * mouse.x, pos.y *mouse.y, pos.z, 1.0);
TexCoord = inTex;
}
