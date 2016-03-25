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
public:
    Ray(): _ori(Point()), _dir(Vector()) {}
    
    //Start from p with direction v
    Ray(const Point &p, const Vector &v): _ori(p), _dir(v) {}
    
    Point getOri() const{return _ori;}
    
    Vector getDir() const{return _dir;}
    
private:
    Point _ori;
    Vector _dir;
};

#endif /* Ray_h */
