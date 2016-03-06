//
//  Ray.h
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Qi Wang. All rights reserved.
//

#ifndef Ray_h
#define Ray_h

#include "Vector.h"
#include "Point.h"

class Ray{
private:
    Point ori;
    Vector dir;
    
public:
    //Default constructor
    Ray(): ori(Point(0.0, 0.0, 0.0)), dir(Vector(0.0, 0.0, 0.0)) {}
    //Constructor
    Ray(const Point &p, const Vector &v): ori(p), dir(v) {}
    Ray(const Point &p, const Point &q): ori(p), dir(Vector(p, q)) {}
    
    //Access private elements
    Point getOri(){return ori;}
    Vector getDir(){return dir;}
};

#endif /* Ray_h */
