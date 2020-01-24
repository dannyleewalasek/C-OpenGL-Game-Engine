#version 330
in vec4 colour2;
in vec2 TexCoord;
uniform sampler2D theTexture;
out vec4 colour;
void main()
{
colour = texture(theTexture, TexCoord) * 0.4 ;
}
