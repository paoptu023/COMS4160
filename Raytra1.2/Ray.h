//
//  Ray.h
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Ray_h
#define Ray_h

#include "Vector.h"
#include "Point.h"

class Ray{
private:
    Point _ori;
    Vector _dir;
    
public:
    //Default constructor
    Ray(): _ori(Point()), _dir(Vector()) {}
    //Constructor
    Ray(const Point &p, const Vector &v): _ori(p), _dir(v) {}
    Ray(const Point &p, const Point &q): _ori(p), _dir(Vector(p, q)) {}
    
    //Access private elements
    Point getOri() const{return _ori;}
    Vector getDir() const{return _dir;}
};

#endif /* Ray_h */
