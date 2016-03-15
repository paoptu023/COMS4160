//
//  Sphere.cc
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Sphere.h"

Sphere::Sphere(Material *&m, const Point &p, const double &r){
    _m = m;
    _center = p;
    _radius = r;
    _min = Point(_center - Vector(_radius + e, _radius + e, _radius + e));
    _max = Point(_center + Vector(_radius - e, _radius - e, _radius - e));
    _bbox = Bbox(_min, _max, -1);
}

bool Sphere::intersect(const Ray &r, Intersection &it){
    Intersection tmp;
    if(!_bbox.intersect(r, tmp) || tmp.getT1() > it.getT1())
        return false;
    
    //Calculate descriminant
    Vector v(_center, r.getOri());
    Vector d = r.getDir();

    double tmp1 = d.dot(v);
    double tmp2 = d.dot(d);
    double tmp3 = v.dot(v) - _radius * _radius;
    double desc = tmp1 * tmp1 - tmp2 * tmp3;
    
    if(desc >= 0){
        double t1;
        Vector d_neg = d * (-1);
        if(desc == 0)                               //One intersection points
            t1 = d_neg.dot(v)/tmp2;
        else                                        //Two intersection points
            t1 = (d_neg.dot(v) - sqrt(desc))/tmp2;

        if(t1 > 0.0001 && t1 < it.getT1()){
            Point p1 = r.getOri() + r.getDir() * t1;
            Vector n = getNormal(p1);
            
            it.set(t1, p1, n, _m);
            return true;
        }
        return false;
    }
    return false;
}

Vector Sphere::getNormal(const Point &p) const{
    Vector n(_center, p);
    n.normalize();
    return move(n);
}