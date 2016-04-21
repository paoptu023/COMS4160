// we are going to be getting an attribute from the main program, named
// "vPosition", one for each vertex.
// on mac you may have to say: "attribute vec4 vPosition;" instead of this:
//attribute vec4 vPosition;
in vec4 vPosition;

// on mac you may have to say: "attribute vec4 vNorm;" instead of this:
//attribute vec4 vNorm;
in vec4 vNorm;

// we are going to be outputting a single 4-vector, called color, which
// may be different for each vertex.
// the fragment shader will be expecting these values, and interpolate
// them according to the distance of the fragment from the vertices
varying vec4 color;

uniform vec4 eye;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 light_position;
uniform vec4 light_ambient;
uniform vec4 light_diffuse;
uniform vec4 light_specular;

uniform vec4 material_ambient;
uniform vec4 material_diffuse;
uniform vec4 material_specular;
uniform float material_shininess;

void main() {
    vec4 light_dir = normalize(light_position - vPosition);
    vec4 eye_dir = normalize(eye - vPosition);
    vec4 half_vec = normalize(light_dir + eye_dir);
    
    //ambient
    vec4 ambient, diffuse, specular;
    ambient = material_ambient * light_ambient;
    
    // diffuse
    float cosnl = max(0.0, dot(vNorm, light_dir));
    diffuse = (material_diffuse * light_diffuse) * cosnl;
    
    //specular
    float cosnh = max(0.0, dot(vNorm, half_vec));
    specular = (material_specular * light_specular) * pow(cosnh, material_shininess);

    color = diffuse + specular + ambient;
    gl_Position = projection * view * vPosition;
} 
