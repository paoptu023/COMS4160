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

class Triangle : public Surface{
private:
    Point _p1, _p2, _p3;
    Vector _n;
    
public:
    Triangle();
    Triangle(double x1, double y1, double z1,
             double x2, double y2, double z2,
             double x3, double y3, double z3, Material *m);
    
    Intersection intersect(const Ray &r);
    
    Vector getNormal(const Point &p){return _n;}
    
    Point getP1() const{return _p1;}
    Point getP2() const{return _p2;}
    Point getP3() const{return _p3;}
    
    string getType(){return "triangle";};
};

#endif /* Triangle_h */
