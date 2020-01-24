#version 330
layout (location = 0) in vec3 pos;
out vec4 colour2;
uniform mat4 projection;
void main()
{
colour2 = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
gl_Position = projection * vec4(pos.x, pos.y, pos.z, 1.0);
}
