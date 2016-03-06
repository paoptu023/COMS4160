//
//  Point.h
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Qi Wang. All rights reserved.
//

#ifndef Point_h
#define Point_h

#include <stdlib.h>
#include "Vector.h"
class Vector;

class Point{
private:
    double x, y, z;
    
public:
    Point(): x(0.0), y(0.0), z(0.0) {}                          //Default constructor
    Point(double u, double v, double w): x(u), y(v), z(w) {}    //Constructor

    //Operator overload
    Point & operator =(const Point &p);
    
    Point operator +(const Vector &v) const;
    Point & operator +=(const Vector &v);
    
    Point operator -(const Vector &v) const;
    Point & operator -=(const Vector &v);
    
    Point operator *(double k) const;
    Point & operator *=(double k);
    
    Point operator /(double k) const;
    Point & operator /=(double k);
    
    //Access private elements
    double getX() const{return x;}
    double getY() const{return y;}
    double getZ() const{return z;}
    
    //Set x, y, z
    void setX(double m){x = m;}
    void setY(double m){y = m;}
    void setZ(double m){z = m;}
    
    //For debug
    void print();
};

#endif /* Point_h */
