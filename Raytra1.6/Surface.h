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
const double eps = 0.000000001;

class Surface{
friend class BVH;
friend class Sorter;
    
public:
    
    Surface(): _m(nullptr), _bbox(Bbox()) {}
    
    virtual bool intersect(const Ray &r,
                           Intersection &it){return false;}
    
    Material* getMaterial() const{return _m;}
    
protected:
    Material *_m;
    Bbox _bbox;
};

#endif /* Surface_h */
