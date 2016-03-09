//
//  Intersection.h
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Intersection_h
#define Intersection_h

#include <stdio.h>
#include <limits>
#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Material.h"

class Intersection{
private:
    double _t1;
    Point _p1;
    Vector _n;
    int _id;

public:
    Intersection();
    
    void set(double t1, const Point &p1, const Vector &n);
    
    Intersection & operator =(const Intersection &i);
    
    double getT1() const{return _t1;}
    
    Point getP1() const{return _p1;}
    
    int getId() const{return _id;}
    
    void setId(int i){_id = i;}
    
    Vector getNormal() const{return _n;}
    
    void print();
};

#endif /* Intersection_h */
