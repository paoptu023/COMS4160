//
//  Triangle.cc
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Triangle.h"

//Default constructor
Triangle::Triangle(){
    _m = Material();
    _p1 = _p2 = _p3 = Point();
    _n = Vector();
    _d = 0.0;
}

//Constructor
Triangle::Triangle(double x1, double y1, double z1,
                   double x2, double y2, double z2,
                   double x3, double y3, double z3, Material &m){
    _p1 = Point(x1, y1, z1);
    _p2 = Point(x2, y2, z2);
    _p3 = Point(x3, y3, z3);
    
    //Calculate normal
    Vector p1_p2 = Vector(_p1, _p2);
    Vector p1_p3 = Vector(_p1, _p3);
    _n = p1_p2.cross(p1_p3);
    _n.normalize();
    
    //Calculate distance from origin
    _d = -Vector(_p1).dot(_n);
    _m = m;
}

//Check intersection
void Triangle::intersect(const Ray &r, Intersection &i){
    double denominator = r.getDir().dot(_n);
    if(denominator == 0)
        return;
    
    double numerator = -(Vector(r.getOri()).dot(_n) + _d);
    double t = numerator / denominator;
    if(t > 0)
        i.initial(t, t, r);
}

