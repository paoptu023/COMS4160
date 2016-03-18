//
//  Plane.h
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Plane_h
#define Plane_h

#include "Surface.h"
#include "Vector.h"

class Plane : public Surface{
public:
    Plane(): _n(Vector()), _d(0.0) {}
    
    Plane(const double &nx, const double &ny,
          const double &nz, const double &d, Material *m);
    
    bool intersect(const Ray &r, Intersection &it);
    
private:
    Vector _n;
    double _d;
};

#endif /* Plane_h */
