//
//  Vector.cc
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Vector.h"

Vector::Vector(double u, double v, double w){
    _xyz[0] = u;
    _xyz[1] = v;
    _xyz[2] = w;
}

//Construct from one point
Vector::Vector(const Point &p){
    _xyz[0] = p[0];
    _xyz[1] = p[1];
    _xyz[2] = p[2];
}

//Construct from two points
Vector::Vector(const Point &p, const Point &q){
    _xyz[0] = q[0] - p[0];
    _xyz[1] = q[1] - p[1];
    _xyz[2] = q[2] - p[2];
}

double Vector::operator[] (const int i) const{
    return _xyz[i];
}

Vector & Vector::operator =(const Vector &v){
    _xyz[0] = v[0];
    _xyz[1] = v[1];
    _xyz[2] = v[2];
    return *this;
}

Vector Vector::operator +(const Vector &v) const{
    return Vector(_xyz[0] + v[0], _xyz[1] + v[1], _xyz[2] + v[2]);
}

Vector & Vector::operator +=(const Vector &v){
    _xyz[0] += v[0];
    _xyz[1] += v[1];
    _xyz[2] += v[2];
    return *this;
}

Vector Vector::operator *(double k) const{
    return Vector(_xyz[0] * k, _xyz[1] * k, _xyz[2] * k);
}

Vector & Vector::operator *=(double k){
    _xyz[0] *= k;
    _xyz[1] *= k;
    _xyz[2] *= k;
    return *this;
}

Vector Vector::operator *(const Vector &v) const{
    return Vector(_xyz[0] * v[0], _xyz[1] * v[1], _xyz[2] * v[2]);
}

Vector & Vector::operator /=(double k){
    _xyz[0] /= k;
    _xyz[1] /= k;
    _xyz[2] /= k;
    return *this;
}

//Dot production
double Vector::dot(const Vector &v) const{
    double x_val = _xyz[0] * v[0];
    double y_val = _xyz[1] * v[1];
    double z_val = _xyz[2] * v[2];
    double val = x_val + y_val + z_val;
    return val;
}

//Cross production
Vector Vector::cross(const Vector &v) const{
    double x_val = _xyz[1] * v[2] - _xyz[2] * v[1];
    double y_val = _xyz[2] * v[0] - _xyz[0] * v[2];
    double z_val = _xyz[0] * v[1] - _xyz[1] * v[0];
    return Vector(x_val, y_val, z_val);
}


//Normalization
void Vector::normalize(){
    double _length = sqrt(_xyz[0] * _xyz[0] + _xyz[1] * _xyz[1] + _xyz[2] * _xyz[2]);
    *this /= _length;
}

double Vector::getLen() const{
   return sqrt(_xyz[0] * _xyz[0] + _xyz[1] * _xyz[1] + _xyz[2] * _xyz[2]);
}

void Vector::print(){
    cout << "Vector :" << _xyz[0] << ", " << _xyz[1] << ", " << _xyz[2] << endl;
}
