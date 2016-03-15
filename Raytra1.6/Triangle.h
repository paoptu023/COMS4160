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
    
    Triangle(const double &x1, const double &y1, const double &z1,
             const double &x2, const double &y2, const double &z2,
             const double &x3, const double &y3, const double &z3, Material *&m);
    
    bool intersect(const Ray &r, Intersection &it);
    
    Vector getNormal(const Point &p) const{return move(_n);}
};

#endif /* Triangle_h */
