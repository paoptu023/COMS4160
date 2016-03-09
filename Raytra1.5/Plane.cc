//
//  Plane.cpp
//  Raytra
//
//  Created by Qi Wang on 2/13/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Plane.h"

Plane::Plane(double nx, double ny, double nz,
             double d, Material *&m){
    _n = Vector(nx, ny, nz);
    _n.normalize();
    _d = d;
    _m = m;
}

bool Plane::intersect(const Ray &r, Intersection &it){
    double denominator = r.getDir().dot(_n);
    if(denominator == 0)
        return false;
    
    double numerator = -(Vector(r.getOri()).dot(_n) + _d);
    double t = numerator / denominator;
    if(t > 0){
        Point p = r.getOri() + r.getDir() * t;
        it.set(t, t, p, p, _n);
        return true;
    }
    return false;
}
