//
//  Sphere.cpp
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Qi Wang. All rights reserved.
//

#include "Sphere.h"

//Check intersection
bool Sphere::intersect(Ray r, double &t1, double &t2){
    //Calculate descriminant
    Vector v(r.getOri(), getCenter());
    Vector d = r.getDir();

    double tmp1 = d.dot(v);
    double tmp2 = d.dot(d);
    double tmp3 = v.dot(v) - getRadius() * getRadius();
    double desc = tmp1 * tmp1 - tmp2 * tmp3;
    
    if(desc < 0)
        return false;
    else{
        Vector d_neg = d * (-1);
        if(desc == 0)                               //One intersecting points
            t1 = t2 = d_neg.dot(v)/tmp2;
        else{                                       //Two intersecting points
            t1 = (d_neg.dot(v) + sqrt(desc))/tmp2;
            t2 = (d_neg.dot(v) - sqrt(desc))/tmp2;
        }
        return true;
    }
}