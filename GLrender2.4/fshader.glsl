varying vec4 light_dir;
//in vec4 light_dir;
varying vec4 eye_dir;
//in vec4 eye_dir;
varying vec4 norm;
//in vec4 norm;
varying vec4 pos;
//in vec4 pos;

uniform float coarseness;

uniform vec4 light_ambient;
uniform vec4 light_diffuse;
uniform vec4 light_specular;

uniform vec4 material_ambient;
uniform vec4 material_diffuse;
uniform vec4 material_specular;
uniform float material_shininess;

void main() {
    vec4 material_d = material_diffuse;
    if (coarseness > 0.0) {
        float width = 2.0 / coarseness;
        float x = floor(pos.x / width);
        float y = floor(pos.y / width);
        float z = floor(pos.z / width);
        // If even sum, white else black
        if (mod(x + y + z, 2.0) > 0.0)
            material_d = vec4(0.96, 0.56, 0.69, 1.0);
        else
            material_d = vec4(1.0, 1.0, 1.0, 1.0);
    }
    
    vec4 half_vec = normalize(light_dir + eye_dir);
    
    //ambient
    vec4 ambient, diffuse, specular;
    ambient = material_ambient * light_ambient;
    
    // diffuse
    float cosnl = max(0.0, dot(norm, light_dir));
    diffuse = (material_d * light_diffuse) * cosnl;
    
    //specular
    float cosnh = max(0.0, dot(norm, half_vec));
    specular = (material_specular * light_specular) * pow(cosnh, material_shininess);
    
    // "gl_FragColor" is already defined for us - it's the one thing you have
    // to set in the fragment shader:
    gl_FragColor = diffuse + specular + ambient;;
} 

