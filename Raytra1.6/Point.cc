//
//  Point.cc
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Point.h"

Point & Point::operator =(const Point &p){
    _xyz[0] = p[0];
    _xyz[1] = p[1];
    _xyz[2] = p[2];
    return *this;
}

Point Point::operator +(const Vector &v) const{
    return move(Point(_xyz[0] + v[0], _xyz[1] + v[1], _xyz[2] + v[2]));
}

Point Point::operator +(const Point &p) const{
    return move(Point(_xyz[0] + p[0], _xyz[1] + p[1], _xyz[2] + p[2]));
}

Point & Point::operator +=(const Vector &v){
    _xyz[0] += v[0];
    _xyz[1] += v[1];
    _xyz[2] += v[2];
    return *this;
}

Point Point::operator -(const Vector &v) const{
    return move(Point(_xyz[0] - v[0], _xyz[1] - v[1], _xyz[2] - v[2]));
}

Point & Point::operator -=(const Vector &v){
    _xyz[0] -= v[0];
    _xyz[1] -= v[1];
    _xyz[2] -= v[2];
    return *this;
}

Point Point::operator /(const int k) const{
    return move(Point(_xyz[0] / k, _xyz[1] / k, _xyz[2] / k));
}

void Point::print(){
    cout << "Point: " << _xyz[0] << " " << _xyz[1] << " " << _xyz[2] << endl;
}