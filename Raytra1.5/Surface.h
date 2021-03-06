//
//  Surface.h
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Surface_h
#define Surface_h

#include "Ray.h"
#include "Material.h"
#include "Bbox.h"
const double e = 0.000000001;

class Surface{
friend class BVH;
    
protected:
    Material *_m;
    Point _min, _max;
    
public:
    Bbox _bbox;
    
    Surface(): _m(NULL), _min(Point()), _max(Point()), _bbox(Bbox()) {}
    
    virtual bool intersect(const Ray &r, Intersection &it, bool bboxOnly){return false;}
    
    Point getMaxP() const {return move(_max);}
    
    Material* getMaterial() const{return _m;}
};

#endif /* Surface_h */
