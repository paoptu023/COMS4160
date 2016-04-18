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

float theta = 0.0;  // rotation around Y axis
float phi = 90.0; // rotation around X axis
float r = 3.0; // distance from center
const float ZENITH = 5.0;
const float NADIR = 175.0;
const float RMAX = 50.0;
const float RMIN = 2.0;

#endif /* glrender_h */
