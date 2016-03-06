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
friend class Triangle;
    
private:
    double _xyz[3];
    
public:
    Point(){_xyz[0] = _xyz[1] = _xyz[2] = 0.0;}
    
    Point(double x, double y, double z);
    
    double operator[] (const int i) const{return _xyz[i];}
    
    Point & operator =(const Point &p);
    
    Point operator +(const Vector &v) const;
    Point & operator +=(const Vector &v);
    
    Point operator +(const Point &p) const;
    
    Point operator -(const Vector &v) const;
    Point & operator -=(const Vector &v);
    
    Point operator /(const int k) const;
    
    void print();                             
};

inline Point::Point(double x, double y, double z){
    _xyz[0] = x;
    _xyz[1] = y;
    _xyz[2] = z;
}

#endif /* Point_h */
