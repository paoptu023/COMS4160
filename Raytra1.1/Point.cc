//
//  Point.cpp
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Qi Wang. All rights reserved.
//

#include "Point.h"

//Operator overload
Point & Point::operator =(const Point &p){
    x = p.getX();
    y = p.getY();
    z = p.getZ();
    return *this;
}

Point Point::operator +(const Vector &v) const{
    return Point(x + v.getX(), y + v.getY(), z + v.getZ());
}

Point & Point::operator +=(const Vector &v){
    x += v.getX();
    y += v.getY();
    z += v.getZ();
    return *this;
}

Point Point::operator -(const Vector &v) const{
    return Point(x - v.getX(), y - v.getY(), z - v.getZ());
}

Point & Point::operator -=(const Vector &v){
    x -= v.getX();
    y -= v.getY();
    z -= v.getZ();
    return *this;
}

Point Point::operator *(double k) const{
    return Point(x * k, y * k, z * k);

}

Point & Point::operator *=(double k){
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

Point Point::operator /(double k) const{
    return Point(x / k, y / k, z / k);
}

Point & Point::operator /=(double k){
    x /= k;
    y /= k;
    z /= k;
    return *this;
}

//For debug
void Point::print(){
    cout << "Point: " << x << " " << y << " " << z << endl;
}