varying vec3 lightv;
varying vec3 viewv;
varying vec4 color;
uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform sampler2D skyMap;
 
void main(void) {
    //vec2 longitudeLatitude = vec2((atan(texCoords.y, texCoords.x) / 3.1415926 + 1.0) * 0.5,
    //                              (asin(texCoords.z) / 3.1415926 + 0.5));
 
    // Apply tiling and offset
    //vec2 texCoordsTransformed = longitudeLatitude * mytexture_ST.xy + mytexture_ST.zw;
 
    //gl_FragColor = texture2D(colorMap, gl_TexCoord[0].st);
    vec3 Light = normalize(lightv);

    vec4 texColor = texture2D(colorMap, gl_TexCoord[0].st);
	 vec4 bump = texture2D(normalMap, gl_TexCoord[0].st);

    vec3 normal = vec3(2.0 * bump - 1.0);
    float diffuse = max(dot(normal, Light), 0.0);
    if (diffuse <= 0.1)
      gl_FragColor = texture2D(skyMap, gl_TexCoord[0].st);
    else
      gl_FragColor = diffuse * texColor;
    //gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}