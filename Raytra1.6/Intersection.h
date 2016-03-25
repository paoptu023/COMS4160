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
#include "Material.h"

class Intersection{
public:
    Intersection();
    
    void set(const double t1, const Vector &n, Material *m);
    
    Intersection & operator =(const Intersection &i);
    
    void setT1(const double t1){_t1 = t1;}
    
    double getT1() const{return _t1;}
    
    Material* getMaterial() const{return _m;}
    
    Vector getNormal() const{return _n;}
    
private:
    double _t1;
    Vector _n;
    Material *_m;
};

#endif /* Intersection_h */
