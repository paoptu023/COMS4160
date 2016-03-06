//
//  Triangle.h
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Triangle_h
#define Triangle_h

#include <stdio.h>
#include "Surface.h"

class Triangle: public Surface{
private:
    Material _m;
    Point _p1, _p2, _p3;
    Vector _n;
    double _d;
    
public:
    //Default constructor
    Triangle();
    //Constructor
    Triangle(double x1, double y1, double z1,
             double x2, double y2, double z2,
             double x3, double y3, double z3, Material &m);
    
    //Check intersection
    void intersect(const Ray &r, Intersection &i);
    
    //Access private elements
    Vector getNormal(const Point &p){return _n;}
    Material getMaterial() const{return _m;}
    
    Point getP1() const{return _p1;}
    Point getP2() const{return _p2;}
    Point getP3() const{return _p3;}
    double getD() const{return _d;}
    
    void getType(){cout << "triangle" << endl;};
};

#endif /* Triangle_h */
