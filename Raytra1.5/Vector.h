//
//  Vector.h
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Vector_h
#define Vector_h

#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "Point.h"
class Point;
using namespace std;

class Vector{
friend class Triangle;
    
private:
    double _xyz[3];

public:
    Vector(){_xyz[0] = _xyz[1] = _xyz[2] = 0.0;}
    
    Vector(double x, double y, double z);
    
    Vector(const Point &p);                     //Construct from one point
    Vector(const Point &p, const Point &q);     //Construct from two points
    
    double operator[] (const int i) const{return move(_xyz[i]);}
    
    Vector & operator =(const Vector &v);
    
    Vector operator +(const Vector &v) const;
    Vector & operator +=(const Vector &v);
    
    Vector operator - (const Vector &v) const;
    
    Vector operator *(double k) const;
    Vector & operator *=(double k);
    
    Vector operator *(const Vector &v) const;   //Per element multiply for RGB
    
    Vector operator /(double k) const;
    
    Vector & operator /=(double k);
    
    double dot(const Vector &v) const;
    
    Vector cross(const Vector &v) const;
    
    void normalize();

    double getLen() const;
    
    void print();                              
};

inline Vector::Vector(double x, double y, double z){
    _xyz[0] = x;
    _xyz[1] = y;
    _xyz[2] = z;
}

inline Vector & Vector::operator =(const Vector &v){
    _xyz[0] = v[0];
    _xyz[1] = v[1];
    _xyz[2] = v[2];
    return *this;
}

inline void Vector::normalize(){
    double length = getLen();
    _xyz[0] /= length;
    _xyz[1] /= length;
    _xyz[2] /= length;
}

#endif /* Vector_h */
