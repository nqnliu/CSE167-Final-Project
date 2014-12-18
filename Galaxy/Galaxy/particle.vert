// vertex shader
#version 330 compatibility
 
uniform mat4x4 matModelview;
uniform mat4x4 matProjection;
 
layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec4 vColor;
 
out vec4 outColor;
 
void main() 
{
    vec4 eyePos = gl_ModelViewMatrix * gl_Vertex;
    gl_Position = gl_ProjectionMatrix * eyePos;
 
	outColor = vColor;
	
	float dist = length(eyePos.xyz);
	float att = inversesqrt(0.1f*dist);
	gl_PointSize = 20.0f * att;
}