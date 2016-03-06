//
//  Sphere.cc
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Sphere.h"

//Check intersection
void Sphere::intersect(const Ray &r, Intersection &i){
    //Calculate descriminant
    Vector v(getCenter(), r.getOri());
    Vector d = r.getDir();

    double tmp1 = d.dot(v);
    double tmp2 = d.dot(d);
    double tmp3 = v.dot(v) - getRadius() * getRadius();
    double desc = tmp1 * tmp1 - tmp2 * tmp3;
    
    if(desc >= 0){
        double t1, t2;
        Vector d_neg = d * (-1);
        if(desc == 0)                               //One intersection points
            t1 = t2 = d_neg.dot(v)/tmp2;
        else{                                       //Two intersection points
            t1 = (d_neg.dot(v) - sqrt(desc))/tmp2;
            t2 = (d_neg.dot(v) + sqrt(desc))/tmp2;
        }
        i.initial(t1, t2, r);
    }
}

//Calculate normal
Vector Sphere::getNormal(const Point &p){
    Vector n(_center, p);
    n.normalize();
    return n;
}