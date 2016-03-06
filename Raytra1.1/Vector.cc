//
//  Vector.cpp
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Qi Wang. All rights reserved.
//

#include "Vector.h"

//Constructor
Vector::Vector(double u, double v, double w){
    x = u;
    y = v;
    z = w;
    length = sqrt(x * x + y * y + z * z);
}

//Construct from two points
Vector::Vector(const Point &p, const Point &q){
    x = q.getX() - p.getX();
    y = q.getY() - p.getY();
    z = q.getZ() - p.getZ();
    length = sqrt(x * x + y * y + z * z);
}

//Operator overload
Vector & Vector::operator =(const Vector &v){
    x = v.getX();
    y = v.getY();
    z = v.getZ();
    length = v.getLen();
    return *this;
}

Vector Vector::operator +(const Vector &v) const{
    return Vector(x + v.getX(), y + v.getY(), z + v.getZ());
}

Vector & Vector::operator +=(const Vector &v){
    x += v.getX();
    y += v.getY();
    z += v.getZ();
    length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    return *this;
}

Vector Vector::operator -(const Vector &v) const{
    return Vector(x - v.getX(), y - v.getY(), z - v.getZ());
}

Vector & Vector::operator -=(const Vector &v){
    x -= v.getX();
    y -= v.getY();
    z -= v.getZ();
    length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    return *this;
}

Vector Vector::operator *(double k) const{
    return Vector(x * k, y * k, z * k);
}

Vector & Vector::operator *=(double k){
    x *= k;
    y *= k;
    z *= k;
    length *= k;
    return *this;
}

Vector Vector::operator /(double k) const{
    return Vector(x / k, y / k, z / k);
}

Vector & Vector::operator /=(double k){
    x /= k;
    y /= k;
    z /= k;
    length /= k;
    return *this;
}

bool Vector::operator ==(const Vector &v){
    return (getX() == v.getX())  &&(getY() == v.getY())  &&(getZ() == v.getZ());
}

//Normalization
void Vector::normalize(){
    length = sqrt(x * x + y * y + z * z);
    *this /= length;
}

//Dot production
double Vector::dot(const Vector &v) const{
    double x_val = getX() * v.getX();
    double y_val = getY() * v.getY();
    double z_val = getZ() * v.getZ();
    double val = x_val + y_val + z_val;
    return val;
}

//Cross production
Vector Vector::cross(const Vector &v) const{
    double x_val = getY() * v.getZ() - getZ() * v.getY();
    double y_val = getZ() * v.getX() - getX() * v.getZ();
    double z_val = getX() * v.getY() - getY() * v.getX();
    return Vector(x_val, y_val, z_val);
}

//For debug
void Vector::print(){
    cout << "Vector :" << getX() << ", " << getY() << ", " << getZ() << endl;
}
