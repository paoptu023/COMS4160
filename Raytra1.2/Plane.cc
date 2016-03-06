//
//  Plane.cpp
//  Raytra
//
//  Created by Qi Wang on 2/13/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Plane.h"

Plane::Plane(double nx, double ny, double nz, double d, const Material &m){
    _m = m;
    _d = d;
    _n = Vector(nx, ny, nz);
    _n.normalize();
}

void Plane::intersect(const Ray &r, Intersection &i){
    double denominator = r.getDir().dot(_n);
    if(denominator == 0)
        return;
    
    double numerator = -(Vector(r.getOri()).dot(_n) + _d);
    double t = numerator / denominator;
    if(t > 0)
        i.initial(t, t, r);
}
