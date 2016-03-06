//
//  Intersection.cc
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Intersection.h"

void Intersection::set(const double t1, const double t2,
                       const Ray &r, const Vector &n){
    _intersect = true;
    _t1 = t1;
    _t2 = t2;
    _p1 = r.getOri() + r.getDir() * t1;
    _p2 = r.getOri() + r.getDir() * t2;
    _n = n;
}

//for bounding box
void Intersection::set(const double t1, const double t2, const Ray &r){
    _intersect = true;
    _t1 = t1;
    _t2 = t2;
    _p1 = r.getOri() + r.getDir() * t1;
    _p2 = r.getOri() + r.getDir() * t2;
}

//Operator overload
Intersection & Intersection::operator =(const Intersection &i){
    _intersect = i._intersect;
    _t1 = i._t1;
    _t2 = i._t2;
    _p1 = i._p1;
    _p2 = i._p2;
    _n = i._n;
    _id = i._id;
    return *this;
}

void Intersection::print(){
    cout << "t1: " << _t1 << "t2: " << _t2 << endl;
    _p1.print();
    _p2.print();
}