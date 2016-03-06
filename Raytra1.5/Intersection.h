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

class Intersection{
private:
    bool _intersect;
    double _t1, _t2;
    Point _p1, _p2;
    Vector _n;
    int _id;

public:
    Intersection();
    
    void set(const double t1, const double t2,
             const Ray &r, const Vector &n);
    
    //for bounding box
    void set(const double t1, const double t2, const Ray &r);
    void setNormal(Vector &n){_n = n;}
    
    //for BVH node
    void setId(const int i){_id = i;}
    int getId() const{return _id;}
    
    Intersection & operator =(const Intersection &i);
    
    bool intersect() const{return _intersect;}
    
    double getT1() const{return _t1;}
    
    double getT2() const{return _t2;}
    
    Point getP1() const{return _p1;}
    
    Point getP2() const{return _p2;}
    
    Vector getNormal() const{return _n;}
    
    void print();
};

inline Intersection::Intersection(){
    _intersect = false;
    _t1 = _t2 = numeric_limits<double>::max();
    _p1 = _p2 = Point();
    _n = Vector();
    _id = -1;
}

#endif /* Intersection_h */
