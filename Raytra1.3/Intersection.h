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
#include "Point.h"
#include "Vector.h"
#include "Ray.h"

class Intersection{
private:
    bool _intersect;
    double _t1, _t2;
    Point _p1, _p2;
    Vector _n;

public:
    Intersection();
    
    //Initialization
    void initial(const double t1, const double t2, const Ray &r);
    
    Intersection & operator =(const Intersection &i);
    
    bool intersect() const{return _intersect;}
    
    double getT1() const{return _t1;}
    
    double getT2() const{return _t2;}
    
    Point getP1() const{return _p1;}
    
    Point getP2() const{return _p2;}
    
    Vector getNormal() const{return _n;}
    
    void setNormal(Vector &n){_n = n;}
    
    void setT1(double k){_t1 = k;}
    
    void print();
};

#endif /* Intersection_h */
