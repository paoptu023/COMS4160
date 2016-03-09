//
//  Intersection.cc
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Intersection.h"

Intersection::Intersection(){
    _t1 = _t2 = numeric_limits<double>::max();
    _p1 = _p2 = Point();
    _n = Vector();
    _id = -1;
}

void Intersection::set(double t1, double t2, const Point &p1,
                       const Point &p2, const Vector &n){
    _t1 = t1;
    _t2 = t2;
    _p1 = p1;
    _p2 = p2;
    _n = n;
}

//Operator overload
Intersection & Intersection::operator =(const Intersection &i){
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