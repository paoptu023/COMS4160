//
//  glrender.h
//  glrender
//
//  Created by Qi Wang on 4/16/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef glrender_h
#define glrender_h

#include "amath.h"

typedef amath::vec4 point4;
typedef amath::vec4 color4;

// Initial up direction
const vec4 upY = vec4(0.0, 1.0, 0.0, 0.0);

// Fixed center
const point4 at = vec4(0.0, 0.0, 0.0, 1.0);

float thetaLat = 0.0;  // rotation around Y axis
float thetaLng = 90.0; // rotation around X axis
float r = 5.0; // distance from center
const float ZENITH = 175.0;
const float NADIR = 5.0;
const float RMAX = 50.0;
const float RMIN = 2.0;

// viewer's position, for lighting calculations
const vec4 viewer = vec4(0.0, 0.0, -1.0, 0.0);

// light & material definitions, again for lighting calculations:
point4 light_position = point4(100.0, 100.0, 100.0, 0.0);
color4 light_ambient = color4(0.2, 0.2, 0.2, 1.0);
color4 light_diffuse = color4(1.0, 1.0, 1.0, 1.0);
color4 light_specular = color4(1.0, 1.0, 1.0, 1.0);

color4 material_ambient = color4(1.0, 0.0, 1.0, 1.0);
color4 material_diffuse = color4(1.0, 0.8, 0.0, 1.0);
color4 material_specular = color4(1.0, 0.8, 0.0, 1.0);
float material_shininess = 100.0;

// product of components, which we will use for shading calculations:
vec4 product(vec4 a, vec4 b) {
    return vec4(a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]);
}

#endif /* glrender_h */
