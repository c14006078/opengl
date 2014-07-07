#version 130
 
varying vec3 Color;
out vec4 outputF;
 
void main()
{
    outputF = vec4(Color,1.0);
    // gl_FragColor = vec4(Color,1.0);
}
