//
//  Point.cc
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Point.h"

//Operator overload
Point & Point::operator =(const Point &p){
    _x = p.getX();
    _y = p.getY();
    _z = p.getZ();
    return *this;
}

Point Point::operator +(const Vector &v) const{
    return Point(_x + v.getX(), _y + v.getY(), _z + v.getZ());
}

Point & Point::operator +=(const Vector &v){
    _x += v.getX();
    _y += v.getY();
    _z += v.getZ();
    return *this;
}

Point Point::operator -(const Vector &v) const{
    return Point(_x - v.getX(), _y - v.getY(), _z - v.getZ());
}

Point & Point::operator -=(const Vector &v){
    _x -= v.getX();
    _y -= v.getY();
    _z -= v.getZ();
    return *this;
}

Point Point::operator *(double k) const{
    return Point(_x * k, _y * k, _z * k);

}

Point & Point::operator *=(double k){
    _x *= k;
    _y *= k;
    _z *= k;
    return *this;
}

Point Point::operator /(double k) const{
    return Point(_x / k, _y / k, _z / k);
}

Point & Point::operator /=(double k){
    _x /= k;
    _y /= k;
    _z /= k;
    return *this;
}

void Point::print(){
    cout << "Point: " << _x << " " << _y << " " << _z << endl;
}