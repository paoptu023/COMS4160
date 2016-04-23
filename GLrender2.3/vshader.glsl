// we are going to be getting an attribute from the main program, named
// "vPosition", one for each vertex.
// on mac you may have to say: "attribute vec4 vPosition;" instead of this:
attribute vec4 vPosition;
//in vec4 vPosition;
attribute vec4 vNorm;
//in vec4 vNorm;

uniform mat4 view;
uniform mat4 projection;

varying vec4 vPos;
varying vec4 norm;

void main() {
    gl_Position = projection * view * vPosition;
    vPos = vPosition;
    norm = vNorm;
} 
