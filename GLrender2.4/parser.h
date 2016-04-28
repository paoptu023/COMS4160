//
//  parser.h
//  glrender
//
//  Created by Qi Wang on 4/22/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef parser_h
#define parser_h

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "amath.h"
#include "bezier.h"
using namespace std;

typedef vec4 point4;

bool is_wavefront_file(const char *file);

void read_wavefront_file (const char *file,
                          vector<point4> &vertices,
                          vector<vec4> &norms);

void read_bezier_file (const char *file,
                       vector<Bezier> &surfaces);

void makeTris (vector<Bezier> &surfaces, vector<point4> &vertices,
               vector<vec4> &norms, const int sample_level);

#endif /* parser_h */
