//
//  Sphere.h
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Sphere_h
#define Sphere_h

#include "Surface.h"

class Sphere: public Surface{
private:
    double _radius;
    Point _center;
    
public:
    Sphere(): _radius(0.0), _center(Point()) {}

    Sphere(Material *&m, const Point &p, double r);
    
    bool intersect(const Ray &r, Intersection &it, bool bboxOnly);
    
    Vector getNormal(const Point &p);
};

#endif /* Sphere_h */
