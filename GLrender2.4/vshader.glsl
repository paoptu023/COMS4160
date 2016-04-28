// we are going to be getting an attribute from the main program, named
// "vPosition", one for each vertex.
// on mac you may have to say: "attribute vec4 vPosition;" instead of this:
attribute vec4 vPosition;
//in vec4 vPosition;
attribute vec4 vNorm;
//in vec4 vNorm;

uniform mat4 view;
uniform mat4 projection;
uniform vec4 eye;
uniform vec4 light_position;

varying vec4 light_dir;
varying vec4 eye_dir;
varying vec4 norm;

varying vec4 pos;

void main() {
    gl_Position = projection * view * vPosition;
    
    light_dir = normalize(light_position - vPosition);
    eye_dir = normalize(eye - vPosition);
    norm = vNorm;
    pos = vPosition;
} 
