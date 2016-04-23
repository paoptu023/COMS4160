varying vec4 vPos;
//in vec4 vPos;

varying vec4 norm;
//in vec4 norm;

uniform vec4 eye;

uniform vec4 light_position;
uniform vec4 light_ambient;
uniform vec4 light_diffuse;
uniform vec4 light_specular;

uniform vec4 material_ambient;
uniform vec4 material_diffuse;
uniform vec4 material_specular;
uniform float material_shininess;

void main() {
    vec4 light_dir = normalize(light_position - vPos);
    vec4 eye_dir = normalize(eye - vPos);
    vec4 half_vec = normalize(light_dir + eye_dir);
    
    //ambient
    vec4 ambient, diffuse, specular;
    ambient = material_ambient * light_ambient;
    
    // diffuse
    float cosnl = max(0.0, dot(norm, light_dir));
    diffuse = (material_diffuse * light_diffuse) * cosnl;
    
    //specular
    float cosnh = max(0.0, dot(norm, half_vec));
    specular = (material_specular * light_specular) * pow(cosnh, material_shininess);
    
    // "gl_FragColor" is already defined for us - it's the one thing you have
    // to set in the fragment shader:
    gl_FragColor = diffuse + specular + ambient;;
} 

