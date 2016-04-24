#include "glrender.h"

// initialization: set up a Vertex Array Object (VAO) and then
void init() {
    theta = 0.0;  
    phi = 90.0;
    r = DEFAULT_R; 
    eye = point4(0.0, 0.0, r, 1.0);
    
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
    glBufferData(GL_ARRAY_BUFFER, 2 * NumVertices * sizeof(vec4), NULL, GL_STATIC_DRAW);
    
    // load in these two shaders...
    // the shaders themselves must be text glsl files in the same directory
    // as we are running this program:
    program = InitShader("vshader.glsl", "fshader.glsl");
 
    // ...and set them to be active
    glUseProgram(program);
    
    // this time, we are sending TWO attributes through: the position of each
    // transformed vertex, and the norm we have calculated in tri()
    
    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    
    // the vPosition attribute is a series of 4-vecs of floats, starting at the
    // beginning of the buffer
    glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint loc2 = glGetAttribLocation(program, "vNorm");
    glEnableVertexAttribArray(loc2);
    glVertexAttribPointer(loc2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(NumVertices * sizeof(vec4)));
    
    // tell the VBO to get the data from the vertices array and the norms array:
    glBufferSubData(GL_ARRAY_BUFFER, 0, NumVertices * sizeof(vec4), &vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, NumVertices * sizeof(vec4),
                    NumVertices * sizeof(vec4), &norms[0]);
    
    eye_pos = glGetUniformLocation(program, "eye");
    view = glGetUniformLocation(program, "view");
    projection = glGetUniformLocation(program, "projection");

    light_p = glGetUniformLocation(program, "light_position");
    light_a = glGetUniformLocation(program, "light_ambient");
    light_d = glGetUniformLocation(program, "light_diffuse");
    light_s = glGetUniformLocation(program, "light_specular");

    material_a = glGetUniformLocation(program, "material_ambient");
    material_d = glGetUniformLocation(program, "material_diffuse");
    material_s = glGetUniformLocation(program, "material_specular");
    material_sh = glGetUniformLocation(program, "material_shininess");

    glUniform4fv(light_p, 1, light_position);
    glUniform4fv(light_a, 1, light_ambient);
    glUniform4fv(light_d, 1, light_diffuse);
    glUniform4fv(light_s, 1, light_specular);
    glUniform4fv(material_a, 1, material_ambient);
    glUniform4fv(material_d, 1, material_diffuse);
    glUniform4fv(material_s, 1, material_specular);
    glUniform1f(material_sh, material_shininess);
    
    // set the background color (white)
    glClearColor(1.0, 1.0, 1.0, 1.0);
}


void display( void ) {
    // clear the window (with white) and clear the z-buffer (which isn't used
    // for this example).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // based on where the mouse has moved to, compute new eye position
    GLfloat lng = DegreesToRadians * theta;
    GLfloat lat = DegreesToRadians * phi;
    
    eye = point4(r * sin(lng) * sin(lat), r * cos(lat), r * sin(lat) * cos(lng), 1.0);
    
    vec4 eye_dir = normalize(eye - at);
    vec4 side = normalize(vec4(cross(upY, eye_dir), 0.0));
    up = normalize(vec4(cross(eye_dir, side), 0.0));
    
    // specify the value of uniform variables
    glUniform4fv(eye_pos, 1, eye);
    // If transpose is GL_TRUE, each matrix is assumed to be supplied in row major order.
    glUniformMatrix4fv(view, 1, GL_TRUE, LookAt(eye, at, up));
    glUniformMatrix4fv(projection, 1, GL_TRUE, perspective);
    
    if(sample_changed){
        makeTris(surfaces, vertices, norms, sample_level);
        NumVertices = (int) vertices.size();
        
        glBufferData(GL_ARRAY_BUFFER, 2 * NumVertices * sizeof(vec4), NULL, GL_STATIC_DRAW);
        
        GLuint loc, loc2;
        loc = glGetAttribLocation(program, "vPosition");
        glEnableVertexAttribArray(loc);
        glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        
        loc2 = glGetAttribLocation(program, "vNorm");
        glEnableVertexAttribArray(loc2);
        glVertexAttribPointer(loc2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(NumVertices * sizeof(vec4)));
        
        glBufferSubData(GL_ARRAY_BUFFER, 0, NumVertices * sizeof(vec4), &vertices[0]);
        glBufferSubData(GL_ARRAY_BUFFER, NumVertices * sizeof(vec4),
                        NumVertices * sizeof(vec4), &norms[0]);
    }
    sample_changed = false;
    
    // draw the VAO:
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    
    // move the buffer we drew into to the screen, and give us access to the one
    // that was there before:
    glutSwapBuffers();
}


void mouse_click (int button, int state, int x, int y) {
    // if the left button of mouse is clicked
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
        lastx = x;
        lasty = y;
    }
}


// use this motionfunc to demonstrate rotation - it adjusts "theta" based
// on how the mouse has moved. Theta is then used the the display callback
// to generate the transformation, ctm, that is applied
// to all the vertices before they are displayed:
void mouse_move_rotate (int x, int y) {
    // keep track of where the mouse was last:
    int amntX = x - lastx;
    int amntY = y - lasty;
    
    if (amntX != 0) {
        theta +=  amntX;
        if (theta > 360.0 ) theta -= 360.0;
        if (theta < 0.0 ) theta += 360.0;
        
        lastx = x;
    }
    
    if (amntY != 0) {
        phi += amntY;
        if (phi < ZENITH) phi = ZENITH;
        if (phi > NADIR) phi = NADIR;
        
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
        theta = 0.0;
        phi = 90.0;
        r = DEFAULT_R;
        eye = point4(0.0, 0.0, r, 1.0);
        
        sample_level = MIN_LEVEL + 1;
        sample_changed = true;
        
        glUniform4fv(eye_pos, 1, eye);
        glUniformMatrix4fv(view, 1, GL_TRUE, LookAt(eye, at, upY));
        glUniformMatrix4fv(projection, 1, GL_TRUE, perspective);
        glutPostRedisplay();
    }
    
    // z moves the camera closer
    if (key == 'z' && r > RMIN) {
        r -= 0.1;
        glutPostRedisplay();
    }
    
    // x moves the view farther
    if (key == 'x' && r < RMAX) {
        r += 0.1;
        glutPostRedisplay();
    }
    
    // decreases detail
    if (key == '<' && sample_level > MIN_LEVEL) {
        sample_level -= 1;
        sample_changed = true;
        glutPostRedisplay();
    }
    
    // increases detail
    if (key == '>' && sample_level < MAX_LEVEL) {
        sample_level += 1;
        sample_changed = true;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
//    if (argc != 2) {
//        std::cerr << "useage: not enough glrender arguements" << std::endl;
//        return -1;
//    }
    char file[] = "twisted_patch.txt";
    
//    read_wavefront_file(argv[1], vertices, norms);
    
    read_bezier_file(file, surfaces);
    makeTris(surfaces, vertices, norms, sample_level);
    NumVertices = (int) vertices.size();
    
    // initialize glut, and set the display modes
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    
    // give us a window in which to display, and set its title:
    glutInitWindowSize(512, 512);
    glutCreateWindow("Rotate / Translate Triangle");
    
    // for displaying things, here is the callback specification:
    glutDisplayFunc(display);
    
    glutMouseFunc(mouse_click);
    // when the mouse is moved, call this function!
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
