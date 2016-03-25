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
    _n = Vector();
    _m = nullptr;
}

void Intersection::set(const double t1, const Vector &n, Material *m){
    _t1 = t1;
    _n = n;
    _m = m;
}

//Operator overload
Intersection & Intersection::operator =(const Intersection &i){
    _t1 = i._t1;
    _n = i._n;
    _m = i._m;
    return *this;
}