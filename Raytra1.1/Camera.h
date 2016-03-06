//
//  camera.h
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Qi Wang. All rights reserved.
//

#ifndef camera_h
#define camera_h

#include "Sphere.h"
#include "Point.h"
#include "Vector.h"
#include "Raytra.h"

class Camera{
private:
    Point eye;
    double f;
    double iw, ih;
    int nw, nh;
    Vector u, v, w;
    
public:
    //Default constructor
    Camera();
    //Constructor
    Camera(const Point &p, const Vector &dir, double d, double width, double height, int nw, int nh);
    
    void setUvw(const Vector &d);           //Set the camera coordinates
    Ray generateRay(double i, double j);    //Generate ray through image point(i, j)
    void render(vector<Surface*> objs);     //Render the image
    void writeFile(const char fileName[]);  //Write result to output file
};

#endif /* camera_h */
