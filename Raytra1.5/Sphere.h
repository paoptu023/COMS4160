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
    Point _center;
    double _radius;
    
public:
    Sphere(): _center(Point()), _radius(0.0) {}

    Sphere(Material *m, const Point &p, double r);
    
    bool intersect(const Ray &r, Intersection &it,
                   const bool &withBbox,
                   const bool &bboxOnly);
    
    Vector getNormal(const Point &p);
    
    Point getCenter() const{return _center;}
    
    double getRadius() const{return _radius;}
    
    string getType(){return "sphere";};
};

#endif /* Sphere_h */
