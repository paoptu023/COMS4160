//
//  Plane.h
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Plane_h
#define Plane_h

#include "Surface.h"
#include "Vector.h"

class Plane: public Surface{
private:
    Material _m;
    Vector _n;
    double _d;
    
public:
    //Default constructor
    Plane(): _m(Material()), _n(Vector()), _d(0.0) {}
    //Constructor
    Plane(double nx, double ny, double nz, double d, const Material &m);
    
    //Check intersection
    void intersect(const Ray &r, Intersection &i);
    
    //Access private elements
    Vector getNormal(const Point &p){return _n;}
    Material getMaterial() const{return _m;}
    double getDistance() const{return _d;}
    
    void getType(){cout << "plane" << endl;};
};

#endif /* Plane_h */
