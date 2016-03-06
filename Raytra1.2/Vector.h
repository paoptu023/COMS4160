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
    double _x, _y, _z;
    double _length;

public:
    Vector():_x(0.0), _y(0.0), _z(0.0) {}       //Default constructor
    Vector(double u, double v, double w);       //Constructor
    Vector(const Point &p);                     //Construct from one point
    Vector(const Point &p, const Point &q);     //Construct from two points
    
    Vector & operator =(const Vector &v);       //Operator overload
    
    Vector operator +(const Vector &v) const;
    Vector & operator +=(const Vector &v);
    
    Vector operator -(const Vector &v) const;
    Vector & operator -=(const Vector &v);
    
    Vector operator *(double k) const;
    Vector & operator *=(double k);
    
    Vector operator /(double k) const;
    Vector & operator /=(double k);
    
    bool operator ==(const Vector &v);
    
    double dot(const Vector &v) const;         //Dot production
    Vector cross(const Vector &v) const;       //Cross production
    void normalize();                          //Normali_zation
    
    double getX() const{return _x;}            //Access private elements
    double getY() const{return _y;}
    double getZ() const{return _z;}
    double getLen() const{return _length;}
    
    void setX(double m){_x = m;}               //Set _x, _y, _z
    void setY(double m){_y = m;}
    void setZ(double m){_z = m;}
    
    void print();                              
};

#endif /* Vector_h */
