#version 330
in vec4 colour2;
uniform vec2 resolution;
uniform vec2 distance;
out vec4 colour;
void main()
{

if (gl_FragCoord.x < resolution.x *0.795 && gl_FragCoord.x > resolution.x* 0.22 && gl_FragCoord.y < resolution.y * 0.79 && gl_FragCoord.y > resolution.y * 0.18){
if (distance.x == 1)
colour = vec4(1.0,0.0,0.0,0.1) ;
else
colour = vec4(0.0,0.0,1.0,0.2) ;
}
else 
colour = vec4(0.0,0.0,0.0,0.0) ;
}
