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
    Material _m;
    Point _center;
    double _radius;
    
public:
    //Default constructor
    Sphere(): _m(Material()), _center(Point()), _radius(0.0) {}
    //Constructor
    Sphere(const Material &m, const Point &p, double r): _m(m), _center(p), _radius(r) {}
    
    //Check intersection
    void intersect(const Ray &r, Intersection &i);
    
    //Calculate normal
    Vector getNormal(const Point &p);
    
    //Access private elements
    Material getMaterial() const{return _m;}
    Point getCenter() const{return _center;}
    double getRadius() const{return _radius;}
    
    void getType(){cout << "sphere" << endl;};
};

#endif /* Sphere_h */
