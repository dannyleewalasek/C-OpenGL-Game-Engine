#version 330
in vec4 colour2;
in vec2 TexCoord;
uniform float test;
uniform sampler2D theTexture;
out vec4 colour;
void main()
{
colour = vec4(1.0,1.0,1.0,0.2);
}
