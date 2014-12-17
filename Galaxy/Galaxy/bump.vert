attribute vec3 tangento;
varying vec3 lightv;
varying vec3 viewv;
varying vec4 color;
varying vec4 texCoords;
 
void main(void) {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;

    vec3 n = gl_NormalMatrix * gl_Normal;
    n = normalize(n);

    vec3 t = gl_NormalMatrix * tangento;
    t = normalize(t);

    vec3 b = cross(n, t);

    vec3 viewe = vec3(gl_ModelViewMatrix * gl_Vertex);
    viewv.x = dot(t, viewe);
    viewv.y = dot(b, viewe);
    viewv.z = dot(n, viewe);

    vec3 lighte = vec3(gl_LightSource[0].position) - viewe;
    lighte = normalize(lighte);
    lightv.x = dot(t, lighte);
    lightv.y = dot(b, lighte);
    lightv.z = dot(n, lighte);

    viewv = normalize(viewv);
    lightv = normalize(lightv);
    color = vec4(tangento, 1.0);
}