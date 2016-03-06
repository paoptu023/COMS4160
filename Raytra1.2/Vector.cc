//
//  Vector.cc
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Vector.h"

//Constructor
Vector::Vector(double u, double v, double w){
    _x = u;
    _y = v;
    _z = w;
    _length = sqrt(_x * _x + _y * _y + _z * _z);
}

//Construct from one point
Vector::Vector(const Point &p){
    _x = p.getX();
    _y = p.getY();
    _z = p.getZ();
    _length = sqrt(_x * _x + _y * _y + _z * _z);
}

//Construct from two points
Vector::Vector(const Point &p, const Point &q){
    _x = q.getX() - p.getX();
    _y = q.getY() - p.getY();
    _z = q.getZ() - p.getZ();
    _length = sqrt(_x * _x + _y * _y + _z * _z);
}

//Operator overload
Vector & Vector::operator =(const Vector &v){
    _x = v.getX();
    _y = v.getY();
    _z = v.getZ();
    _length = v.getLen();
    return *this;
}

Vector Vector::operator +(const Vector &v) const{
    return Vector(_x + v.getX(), _y + v.getY(), _z + v.getZ());
}

Vector & Vector::operator +=(const Vector &v){
    _x += v.getX();
    _y += v.getY();
    _z += v.getZ();
    _length = sqrt(_x * _x + _y * _y + _z * _z);
    return *this;
}

Vector Vector::operator -(const Vector &v) const{
    return Vector(_x - v.getX(), _y - v.getY(), _z - v.getZ());
}

Vector & Vector::operator -=(const Vector &v){
    _x -= v.getX();
    _y -= v.getY();
    _z -= v.getZ();
    _length = sqrt(_x * _x + _y * _y + _z * _z);
    return *this;
}

Vector Vector::operator *(double k) const{
    return Vector(_x * k, _y * k, _z * k);
}

Vector & Vector::operator *=(double k){
    _x *= k;
    _y *= k;
    _z *= k;
    _length *= k;
    return *this;
}

Vector Vector::operator /(double k) const{
    return Vector(_x / k, _y / k, _z / k);
}

Vector & Vector::operator /=(double k){
    _x /= k;
    _y /= k;
    _z /= k;
    _length /= k;
    return *this;
}

bool Vector::operator ==(const Vector &v){
    return (_x == v.getX())  &&(_y == v.getY())  &&(_z == v.getZ());
}

//Normalization
void Vector::normalize(){
    _length = sqrt(_x * _x + _y * _y + _z * _z);
    *this /= _length;
}

//Dot production
double Vector::dot(const Vector &v) const{
    double x_val = _x * v.getX();
    double y_val = _y * v.getY();
    double z_val = _z * v.getZ();
    double val = x_val + y_val + z_val;
    return val;
}

//Cross production
Vector Vector::cross(const Vector &v) const{
    double x_val = _y * v.getZ() - _z * v.getY();
    double y_val = _z * v.getX() - _x * v.getZ();
    double z_val = _x * v.getY() - _y * v.getX();
    return Vector(x_val, y_val, z_val);
}

void Vector::print(){
    cout << "Vector :" << _x << ", " << _y << ", " << _z << endl;
}
