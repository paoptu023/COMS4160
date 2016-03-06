//
//  Shape.h
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Qi Wang. All rights reserved.
//

#ifndef Shape_h
#define Shape_h

#include "Raytra.h"
#include "Ray.h"

class Surface{
private:
    Point center;
    
public:
    virtual bool intersect(Ray r, double &t1, double &t2){return false;}
    virtual Point getCenter(){return center;};
};

#endif /* Shape_h */
