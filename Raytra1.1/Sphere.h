//
//  Sphere.h
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Qi Wang. All rights reserved.
//

#ifndef Sphere_h
#define Sphere_h

#include "Surface.h"

class Sphere: public Surface{
private:
    Point center;
    double radius;
    
public:
    //Default constructor
    Sphere(): center(Point(0.0, 0.0, 0.0)), radius(0.0) {}
    //Constructor
    Sphere(const Point &p, double r): center(p), radius(r) {}
    
    //Access private elements
    Point getCenter() const{return center;}
    double getRadius() const{return radius;}
    
    //Check intersection
    bool intersect(Ray r, double &t1, double &t2);
};

#endif /* Sphere_h */
