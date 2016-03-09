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

class Surface{
friend class BVH;
protected:
    Material *_m;
    Point _min, _max;
    Bbox _bbox;
    
public:
    
    Surface(): _m(NULL), _min(Point()), _max(Point()), _bbox(Bbox()) {}
    
    virtual bool intersect(const Ray &r, Intersection &it, bool &bboxOnly){return false;}
    
    Material* getMaterial() const{return _m;}
};

#endif /* Surface_h */
