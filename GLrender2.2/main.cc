#include "glrender.h"
#include <vector>

GLuint buffers[2];
GLint matrix_loc;

// array of vertices
std::vector<point4> vertices;
// array of norms
std::vector<vec4> norms;

// Camera position
point4 eye;
// Up vector
vec4 up;
// Transformation matrix from world space to camera space
mat4 View;

// Location of program objects
GLuint eye_pos;
GLuint view;
GLuint projection;

//shaders
GLuint program;

//void tri()
//{
//    for(int i = 0; i < (int)vertices.size() / 3; ++i){
//        // compute the lighting at each vertex, then set it as the color there:
//        vec3 n1 = normalize(cross(ctm * vertices[3 * i + 1] - ctm * vertices[3 * i],
//                                  ctm * vertices[3 * i + 2] - ctm * vertices[3 * i + 1]));
//        vec4 n = vec4(n1[0], n1[1], n1[2], 0.0);
//        vec4 half = normalize(light_position+viewer);
//        color4 ambient_color, diffuse_color, specular_color;
//        
//        ambient_color = product(material_ambient, light_ambient);
//        float dd = dot(light_position, n);
//        
//        if(dd>0.0) diffuse_color = dd * product(light_diffuse, material_diffuse);
//        else diffuse_color =  color4(0.0, 0.0, 0.0, 1.0);
//        
//        dd = dot(half, n);
//        if(dd > 0.0) specular_color = exp(material_shininess * log(dd)) * product(light_specular, material_specular);
//        else specular_color = vec4(0.0, 0.0, 0.0, 1.0);
//        
//        
//        // now transform the vertices according to the ctm transformation matrix,
//        // and set the colors for each of them as well. as we are going to give
//        // flat shading, we will ingore the specular component for now.
//        colors[3 * i] = ambient_color + diffuse_color;
//        colors[3 * i + 1] = ambient_color + diffuse_color;
//        colors[3 * i + 2] = ambient_color + diffuse_color;
//    }
//}


// initialization: set up a Vertex Array Object (VAO) and then
void init() {
    // create a vertex array object - this defines mameory that is stored
    // directly on the GPU
    GLuint vao;
    
    // deending on which version of the mac OS you have, you may have to do this:
#ifdef __APPLE__
    glGenVertexArraysAPPLE( 1, &vao );  // give us 1 VAO:
    glBindVertexArrayAPPLE( vao );      // make it active
#else
    glGenVertexArrays( 1, &vao );   // give us 1 VAO:
    glBindVertexArray( vao );       // make it active
#endif
    
    // set up vertex buffer object - this will be memory on the GPU where
    // we are going to store our vertex data
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);  // make it active
    
    // specify that its part of a VAO, what its size is, and where the
    // data is located, and finally a "hint" about how we are going to use
    // the data (the driver will put it in a good memory location, hopefully)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(point4) +
                 norms.size() * sizeof(point4), NULL, GL_STATIC_DRAW);
    
    // tell the VBO to get the data from the vertices array and the colors array:
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(point4), &vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(point4),
                    norms.size() * sizeof(point4), &norms[0]);
    
    // load in these two shaders...  (note: InitShader is defined in the
    // accompanying initshader.c code).
    // the shaders themselves must be text glsl files in the same directory
    // as we are running this program:
    program = InitShader("vshader_passthrough.glsl", "fshader_passthrough.glsl");
 
    // ...and set them to be active
    glUseProgram(program);
    
    
    // this time, we are sending TWO attributes through: the position of each
    // transformed vertex, and the color we have calculated in tri()
    
    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    
    // the vPosition attribute is a series of 4-vecs of floats, starting at the
    // beginning of the buffer
    glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint loc2 = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(loc2);

    // the vColor attribute is a series of 4-vecs of floats, starting just after
    // the points in the buffer
    glVertexAttribPointer(loc2, 4, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(vertices.size() * sizeof(point4)));
    
    eye_pos = glGetUniformLocation(program, "eye");
    view = glGetUniformLocation(program, "view");
    projection = glGetUniformLocation(program, "projection");
    
    // set the background color (white)
    glClearColor(1.0, 1.0, 1.0, 1.0);
}


void display( void ) {
    // clear the window (with white) and clear the z-buffer (which isn't used
    // for this example).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // based on where the mouse has moved to, construct a transformation matrix:
    // compute new eye and up vector
    GLfloat lat = DegreesToRadians * thetaLat;
    GLfloat lng = DegreesToRadians * thetaLng;
    
    eye = point4(r * sin(lng) * sin(lat), r * cos(lng), r * sin(lng) * cos(lat), 1.0);
    vec4 eye_dir = normalize(eye - at);
    vec4 ortho = normalize(cross(upY, eye_dir));
    up = normalize(vec4(cross(eye_dir, ortho), 0.0));
    
    // specify the value of uniform variables
    glUniform4fv(eye_pos, 1, eye);
    glUniformMatrix4fv(view, 1, GL_FALSE, LookAt(eye, at, up));
    glUniformMatrix4fv(projection, 1, GL_FALSE, Perspective(45.0, 1.0, 1.0, 50.0));
    
    // draw the VAO:
    glDrawArrays(GL_TRIANGLES, 0, (int)vertices.size());
    
    // move the buffer we drew into to the screen, and give us access to the one
    // that was there before:
    glutSwapBuffers();
}


// use this motionfunc to demonstrate rotation - it adjusts "theta" based
// on how the mouse has moved. Theta is then used the the display callback
// to generate the transformation, ctm, that is applied
// to all the vertices before they are displayed:
void mouse_move_rotate (int x, int y) {
    // keep track of where the mouse was last:
    static int lastx = 0;
    static int lasty = 0;
    
    int amntX = x - lastx;
    int amntY = y - lasty;
    
    if (amntX != 0) {
        thetaLat +=  amntX;
        if (thetaLat > 360.0 ) thetaLat -= 360.0;
        if (thetaLat < 0.0 ) thetaLat += 360.0;
        
        lastx = x;
    }

    if (amntY != 0) {
        thetaLng += amntY;
        if (thetaLng > ZENITH) thetaLng = ZENITH;
        if (thetaLng < NADIR) thetaLng = NADIR;
        
        lasty = y;
    }

    // force the display routine to be called as soon as possible:
    glutPostRedisplay();
    
}


// the keyboard callback, called whenever the user types something with the
// regular keys.
void mykey(unsigned char key, int mousex, int mousey) {
    if(key=='q'||key=='Q') exit(0);
    
    // and r resets the view:
    if (key =='r') {
        thetaLat = 0.0;
        thetaLng = 90.0;
        eye = point4(0.0, 0.0, r, 1.0);
        up = upY;
        View = LookAt(eye, at, up);
        glutPostRedisplay();
    }
}

void read_wavefront_file (const char *file, std::vector<point4> &vertices);

int main(int argc, char** argv) {
//    if (argc != 2) {
//        std::cerr << "useage: not enough glrender arguements" << std::endl;
//        return -1;
//    }
    char file[] = "kitten.obj";
    
//    read_wavefront_file(argv[1], vertices);
    read_wavefront_file(file, vertices);
    norms = std::vector<point4>(vertices.size(), point4(0.0, 0.5f, 0.0, 1.0));
    
    // initialize glut, and set the display modes
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    
    // give us a window in which to display, and set its title:
    glutInitWindowSize(512, 512);
    glutCreateWindow("Rotate / Translate Triangle");
    
    // for displaying things, here is the callback specification:
    glutDisplayFunc(display);
    
    // when the mouse is moved, call this function!
    // you can change this to mouse_move_translate to see how it works
    glutMotionFunc(mouse_move_rotate);
 
    // for any keyboard activity, here is the callback:
    glutKeyboardFunc(mykey);
    
#ifndef __APPLE__
    // initialize the extension manager: sometimes needed, sometimes not!
    glewInit();
#endif

    // call the init() function, defined above:
    init();
    
    // enable the z-buffer for hidden surface removel:
    glEnable(GL_DEPTH_TEST);

    // once we call this, we no longer have control except through the callbacks:
    glutMainLoop();
    return 0;
}
