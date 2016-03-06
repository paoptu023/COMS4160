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
    double _a, _b, _c, _d, _e, _f;
    
public:
    Triangle();
    Triangle(double x1, double y1, double z1,
             double x2, double y2, double z2,
             double x3, double y3, double z3, Material *m);
    
    bool intersect(const Ray &r, Intersection &it,
                   const bool &withBbox,
                   const bool &bboxOnly);
    
    Vector getNormal(const Point &p){return move(_n);}
    
    Point getP1(){return _p1;}
    Point getP2(){return _p2;}
    Point getP3(){return _p3;}
    
    string getType(){return "triangle";};
};

#endif /* Triangle_h */
