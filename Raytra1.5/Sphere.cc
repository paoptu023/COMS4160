//
//  Sphere.cc
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Sphere.h"

Sphere::Sphere(Material *&m, const Point &p, double r){
    _m = m;
    _center = p;
    _radius = r;
    _min = Point(_center - Vector(_radius + e, _radius + e, _radius + e));
    _max = Point(_center + Vector(_radius - e, _radius - e, _radius - e));
    _bbox = Bbox(_min, _max, -1);
}

bool Sphere::intersect(const Ray &r, Intersection &it, bool bboxOnly){
    if(!_bbox.intersect(r, it))
        return false;
    
    if(bboxOnly)
        return true;
    
    //Calculate descriminant
    Vector v(_center, r.getOri());
    Vector d = r.getDir();

    double tmp1 = d.dot(v);
    double tmp2 = d.dot(d);
    double tmp3 = v.dot(v) - _radius * _radius;
    double desc = tmp1 * tmp1 - tmp2 * tmp3;
    
    if(desc >= 0){
        double t1, t2;
        Vector d_neg = d * (-1);
        if(desc == 0)                               //One intersection points
            t1 = t2 = d_neg.dot(v)/tmp2;
        else{                                       //Two intersection points
            t1 = (d_neg.dot(v) - sqrt(desc))/tmp2;
//            t2 = (d_neg.dot(v) + sqrt(desc))/tmp2;
        }

        Point p1 = r.getOri() + r.getDir() * t1;
//        Point p2 = r.getOri() + r.getDir() * t2;
        Vector n = getNormal(p1);
        
        it.set(t1, p1, n);
        return true;
    }
    return false;
}

Vector Sphere::getNormal(const Point &p){
    Vector n(_center, p);
    n.normalize();
    return move(n);
}