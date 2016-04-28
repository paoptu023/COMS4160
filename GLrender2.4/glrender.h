//
//  glrender.h
//  glrender
//
//  Created by Qi Wang on 4/16/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef glrender_h
#define glrender_h

#include "parser.h"

typedef vec4 point4;

// Initial up direction
const vec4 upY = vec4(0.0, 1.0, 0.0, 0.0);

// Fixed center
const point4 at = point4(0.0, 0.0, 0.0, 1.0);

const float DEFAULT_R = 15.0;
const float ZENITH = 5.0;
const float NADIR = 175.0;
const float RMAX = 50.0;
const float RMIN = 2.0;

bool sample_changed = false;
const int MIN_LEVEL = 2;
const int MAX_LEVEL = 20;
int sample_level = MIN_LEVEL + 3;

// light & material definitions, again for lighting calculations:
vec4 light_position = vec4(100.0, 100.0, 100.0, 1.0);
vec4 light_ambient = vec4(0.2, 0.2, 0.2, 1.0);
vec4 light_diffuse = vec4(1.0, 1.0, 1.0, 1.0);
vec4 light_specular = vec4(1.0, 1.0, 1.0, 1.0);

vec4 material_ambient = vec4(1.0, 0.0, 1.0, 1.0);
vec4 material_diffuse = vec4(1.0, 0.8, 0.0, 1.0);
vec4 material_specular = vec4(1.0, 0.8, 0.0, 1.0);
float material_shininess = 100.0;

GLuint buffers[2];
GLint matrix_loc;

// array of vertices
std::vector<point4> vertices;
// array of norms
std::vector<vec4> norms;
// array of bezier surfaces
std::vector<Bezier> surfaces;

int NumVertices;

// Camera position
point4 eye;
vec4 up;

float r;     // distance from center
float theta; // rotation around Y axis
float phi;   // rotation around X axis

int lastx = 0;
int lasty = 0;

mat4 perspective = Perspective(40.0, 1.0, 1.0, 50.0);

float coarseness = 2.0;
// Location of program objects
GLuint coarse;

GLuint eye_pos;
GLuint view;
GLuint projection;

GLuint light_p;
GLuint light_a;
GLuint light_d;
GLuint light_s;

GLuint material_a;
GLuint material_d;
GLuint material_s;
GLuint material_sh;

//shaders
GLuint program;

#endif /* glrender_h */
