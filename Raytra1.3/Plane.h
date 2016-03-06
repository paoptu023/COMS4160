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
private:
    Vector _n;
    double _d;
    
public:
    Plane(): _n(Vector()), _d(0.0) {}
    Plane(double nx, double ny, double nz, double d, Material *m);

    Intersection intersect(const Ray &r);
    
    Vector getNormal(){return _n;}
    
    double getDistance() const{return _d;}
    
    string getType(){return "plane";};
};

#endif /* Plane_h */
