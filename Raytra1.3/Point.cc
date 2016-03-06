//
//  Point.cc
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Point.h"

double Point::operator[] (const int i) const{
    return _xyz[i];
}

Point & Point::operator =(const Point &p){
    _xyz[0] = p[0];
    _xyz[1] = p[1];
    _xyz[2] = p[2];
    return *this;
}

Point Point::operator +(const Vector &v) const{
    return Point(_xyz[0] + v[0], _xyz[1] + v[1], _xyz[2] + v[2]);
}

Point & Point::operator +=(const Vector &v){
    _xyz[0] += v[0];
    _xyz[1] += v[1];
    _xyz[2] += v[2];
    return *this;
}

Point Point::operator -(const Vector &v) const{
    return Point(_xyz[0] - v[0], _xyz[1] - v[1], _xyz[2] - v[2]);
}

Point & Point::operator -=(const Vector &v){
    _xyz[0] -= v[0];
    _xyz[1] -= v[1];
    _xyz[2] -= v[2];
    return *this;
}

void Point::print(){
    cout << "Point: " << _xyz[0] << " " << _xyz[1] << " " << _xyz[2] << endl;
}