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
#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>
#include "AmbientLight.h"
#include "PointLight.h"
#include "Surface.h"
#include "Point.h"
#include "Vector.h"
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
    //Default constructor
    Camera();
    //Constructor
    void initial(const Point &p, const Vector &dir,
                 double d, double iw, double ih,
                 int pw, int ph);
    
    //Set the camera coordinates
    void setUvw(const Vector &d);
    
    //Generate ray through image point(i, j)
    Ray generateRay(double i, double j);
    
    //Render the image
    void render(const vector<Surface*> &objects,
                const AmbientLight &aLight,
                const vector<PointLight*> &pLights);
    
    vector<double> calcShading(const Intersection &inter, const Point &lPos,
                               const vector<double> &lRgb, const Material &m);
    
    //Write result to output file
    void writeFile(const char fileName[]);
};

#endif /* Camera_h */
