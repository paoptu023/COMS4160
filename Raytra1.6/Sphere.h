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
public:
    Sphere(): _radius(0.0), _center(Point()) {}
    
    Sphere(Material *&m, const Point &p, const double &r);
    
    bool intersect(const Ray &r, Intersection &it);
    
    Vector getNormal(const Point &p) const;
    
private:
    double _radius;
    Point _center;
};

#endif /* Sphere_h */
