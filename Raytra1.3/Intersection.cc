//
//  Intersection.cc
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Intersection.h"

Intersection::Intersection(){
    _intersect = false;
    _t1 = _t2 = 0.0;
    _p1 = _p2 = Point();
    _n = Vector();
}

void Intersection::initial(const double t1, const double t2, const Ray &r){
    if(t1 > 0 && t2 > 0){
        _intersect = true;
        _t1 = t1;
        _t2 = t2;
        _p1 = r.getOri() + r.getDir() * t1;
        _p2 = r.getOri() + r.getDir() * t2;
    }
}

//Operator overload
Intersection & Intersection::operator =(const Intersection &i){
    _intersect = i.intersect();
    _t1 = i.getT1();
    _t2 = i.getT2();
    _p1 = i.getP1();
    _p2 = i.getP2();
    _n = i.getNormal();
    return *this;
}

void Intersection::print(){
    cout << "t1: " << _t1 << "t2: " << _t2 << endl;
    _p1.print();
    _p2.print();
}