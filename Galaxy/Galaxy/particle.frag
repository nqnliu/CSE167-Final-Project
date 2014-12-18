// fragment shader
#version 330
 
uniform sampler2D tex;
 
in vec4 outColor;
 
out vec4 vFragColor;
 
void main() 
{
	vFragColor = vec4(1.0, 0.0, 0.0, 0.5);
}