//
//  Vector.h
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Qi Wang. All rights reserved.
//

#ifndef Vector_h
#define Vector_h

#include "Point.h"
class Point;
#include "Raytra.h"

class Vector{
private:
    double x, y, z;
    double length;

public:
    Vector():x(0.0), y(0.0), z(0.0) {}          //Default constructor
    Vector(double u, double v, double w);       //Constructor
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
    
    double dot(const Vector &v) const;          //Dot production
    Vector cross(const Vector &v) const;        //Cross production
    void normalize();                           //Normalization
    
    double getX() const{return x;}              //Access private elements
    double getY() const{return y;}
    double getZ() const{return z;}
    double getLen() const{return length;}
    
    void setX(double m){x = m;}                 //Set x, y, z
    void setY(double m){y = m;}
    void setZ(double m){z = m;}
    
    void print();                               //For debug
};

#endif /* Vector_h */
