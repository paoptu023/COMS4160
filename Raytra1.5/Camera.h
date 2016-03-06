//
//  Camera.h
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include <stdlib.h>
#include <vector>
#include <limits>
#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>
#include "Light.h"
#include "Surface.h"
#include "Point.h"
#include "Vector.h"
#include "BVH.h"
using namespace Imf;
using namespace Imath;
using namespace std;

class Camera{
private:
    Point _eye;
    double _f;
    double _iw, _ih;
    int _pw, _ph;
    Vector _u, _v, _w;
    Array2D<Rgba> _pixels;
    
public:
    Camera();
    
    Camera(const Point &p, const Vector &dir,
           double d, double iw, double ih,
           int pw, int ph);
    
    //Set the camera coordinates
    void setUvw(const Vector &d);
    
    //Generate ray through image point(i, j)
    Ray generateRay(double i, double j);
    
    //Render the image
    void render(vector<Surface*> &objects,
                const vector<Light*> &lights,
                const AmbientLight *aLight,
                const bool &withBbox,
                const bool &bboxOnly);
    
    //Recursive ray tracing
    Vector rayColor(const Ray &r, int ray_type, int recurse_limit,
                    const vector<Light*> lights,
                    const vector<Surface*> objects,
                    const AmbientLight *aLight, BVH *node,
                    const bool &withBbox, const bool &bboxOnly);
    
    void setPixel(int x, int y, double r, double g, double b){
        Rgba &px = _pixels[y][x];
        px.r = r; px.g = g; px.b = b;
    }
    
    //Write result to output file
    void writeFile(const char fileName[]);
};

#endif /* Camera_h */
