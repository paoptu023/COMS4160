//
//  Intersection.cc
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Intersection.h"

Intersection::Intersection(){
    _t1 = numeric_limits<double>::max();
    _p1 = Point();
    _n = Vector();
    _id = -1;
}

void Intersection::set(double t1, const Point &p1, const Vector &n){
    _t1 = t1;
    _p1 = p1;
    _n = n;
}

//Operator overload
Intersection & Intersection::operator =(const Intersection &i){
    _t1 = i._t1;
    _p1 = i._p1;
    _n = i._n;
    _id = i._id;
    return *this;
}

void Intersection::print(){
    cout << "t1: " << _t1 <<  endl;
    _p1.print();
}