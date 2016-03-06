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
private:
    double _xyz[3];

public:
    Vector(){
        _xyz[0] = _xyz[1] = _xyz[2] = 0.0;
    }
    
    Vector(double x, double y, double z);
    
    Vector(const Point &p);                     //Construct from one point
    Vector(const Point &p, const Point &q);     //Construct from two points
    
    double operator[] (const int i) const;
    
    Vector & operator =(const Vector &v);
    
    Vector operator +(const Vector &v) const;
    Vector & operator +=(const Vector &v);
    
    Vector operator *(double k) const;
    Vector & operator *=(double k);
    
    Vector operator *(const Vector &v) const;   //Per element multiply for RGB
    
    Vector & operator /=(double k);
    
    double dot(const Vector &v) const;
    
    Vector cross(const Vector &v) const;
    
    void normalize();

    double getLen() const;
    
    void print();                              
};

#endif /* Vector_h */
