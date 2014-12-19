// fragment shader
#version 330
 
uniform sampler2D tex;
 
in vec4 outColor;
 
out vec4 vFragColor;
 
void main() 
{
   highp vec4 texture = texture2D(tex, gl_PointCoord);
   if (texture.x <= .1 && texture.y <= .1 && texture.z <= .1)
   {
      texture.w = 0;
   }
	vFragColor = outColor;
   //vFragColor= texture2D(tex, gl_PointCoord) * outColor;
}