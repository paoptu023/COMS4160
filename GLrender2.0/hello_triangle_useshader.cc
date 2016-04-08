// Very simple display triangle program, using vertex shader to color it RG&B

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#endif 

#include "amath.h"


typedef amath::vec4  point4;

GLuint buffers[1]; // space for the name of one buffer object

point4  points[3] = {
    point4(-0.25,0.0,0.0, 1.0),
    point4( 0.25,0.0,0.0, 1.0),
    point4( 0.0, 0.5,0.0, 1.0)};

GLuint program; // name of the shader program


// initialization: set up a Vertex Array Object (VAO) and then 
void init()
{
    
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
    // we are going to store our vertex data (that is currently in the "points"
    // array)
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);  // make it active
    
    // specify that its part of a VAO, what its size is, and where the
    // data is located, and finally a "hint" about how we are going to use
    // the data (the driver will put it in a good memory location, hopefully)
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    
    // load in these two shaders...  (note: InitShader is defined in the
    // accompanying initshader.cc code).
    // the shaders themselves must be text glsl files in the same directory
    // as we are running this program:
    program = InitShader("vshader_assign_tri_rgb.glsl", "fshader_passthrough.glsl");
    
    // ...and set them to be active
    glUseProgram(program);
    
    // set up an attribute called "vPosition" which will be sent to the vertex shader
    GLuint loc;
    loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    
    // the attribute will be from our VAO, each element will be 4 floats,
    // starting form the beginning of the buffer:
    glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    
    // set the background color (white)
    glClearColor(0.0, 0.0, 0.0, 1.0);
}


// the display callback function (see it get registered in main()).
// this gets called every time the display needs updating, such as when a
// window is exposed or hidden, or any time your own code called 
void display( void )
{
    // clear the window (with white) and clear the z-buffer (which isn't used
    // for this example).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // draw the VAO as 3 triangles
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // move the buffer we drew into to the screen, and give us access to the one
    // that was there before:
    glutSwapBuffers();
}



// the keyboard callback, called whenever the user types something with the
// regular keys. 
void mykey(unsigned char key, int mousex, int mousey)
{
    // if the key is one of these, exit the program
    if(key=='q'||key=='Q') exit(0);
}



int main(int argc, char** argv)
{
    
    // initialize glut, and set the display modes
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    
    // give us a window in which to display, and set its title:
    glutInitWindowSize(512, 512);
    glutCreateWindow("Hello Triangle");
    
    // for displaying things, here is the callback specification:
    glutDisplayFunc(display);
    
    // for any keyboard activity, here is the callback:
    glutKeyboardFunc(mykey);
    
#ifndef __APPLE__
    // initialize the extension manager: sometimes needed, sometimes not!
    glewInit();
#endif
    
    // call the init() function, defined above:
    init();
    
    // once we call this, we no longer have control except through the callbacks:
    glutMainLoop();
    
    return 0;
}
