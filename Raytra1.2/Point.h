//
//  Point.h
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Point_h
#define Point_h

#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "Vector.h"
class Vector;
using namespace std;

class Point{
private:
    double _x, _y, _z;
    
public:
    Point(): _x(0.0), _y(0.0), _z(0.0) {}                          //Default constructor
    Point(double x, double y, double z): _x(x), _y(y), _z(z) {}    //Constructor

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
    
    double getX() const{return _x;}             //Access private elements
    double getY() const{return _y;}
    double getZ() const{return _z;}
    
    void setX(double m){_x = m;}                //Set _x, _y, _z
    void setY(double m){_y = m;}
    void setZ(double m){_z = m;}
    
    void print();                             
};

#endif /* Point_h */
