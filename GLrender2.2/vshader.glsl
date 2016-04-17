// we are going to be getting an attribute from the main program, named
// "vPosition", one for each vertex.
// on mac you may have to say: "attribute vec4 vPosition;" instead of this:
attribute vec4 vPosition;
//in vec4 vPosition;

// on mac you may have to say: "attribute vec4 vNorm;" instead of this:
attribute vec4 vNorm;
//in vec4 vNorm;

// we are going to be outputting a single 4-vector, called color, which
// may be different for each vertex.
// the fragment shader will be expecting these values, and interpolate
// them according to the distance of the fragment from the vertices
varying vec4 color;

uniform vec4 eye;
uniform mat4 view;
uniform mat4 projection;

// light & material definitions, again for lighting calculations:
struct light {
    vec4 position;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

light l = light(vec4(100.0, 100.0, 100.0, 1.0),
                vec4(0.2, 0.2, 0.2, 1.0),
                vec4(1.0, 1.0, 1.0, 1.0),
                vec4(1.0, 1.0, 1.0, 1.0));

struct material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

material m = material(vec4(1.0, 0.0, 1.0, 1.0),
                      vec4(1.0, 0.8, 0.0, 1.0),
                      vec4(1.0, 1.0, 1.0, 1.0),
                      100.0);

void main() {
    vec4 light_dir = normalize(l.position - vPosition);
    vec4 eye_dir = normalize(eye - vPosition);
    vec4 half_vec = normalize(light_dir + eye_dir);
    
    //ambient
    vec4 ambient, diffuse, specular;
    ambient = m.ambient * l.ambient;
    
    // diffuse
    float cosnl = max(0.0, dot(vNorm, light_dir));
    diffuse = (m.diffuse * l.diffuse) * cosnl;
    
    //specular
    float cosnh = max(0.0, dot(vNorm, half_vec));
    specular = (m.specular * l.specular) * pow(cosnh, m.shininess);

    color = diffuse + specular;
    gl_Position = projection * view * vPosition;
} 
