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
protected:
    Material *_m;
    
public:
    Bbox _bbox;
    Surface(): _m(NULL), _bbox(Bbox()) {}
    
    virtual bool intersect(const Ray &r, Intersection &it,
                           const bool &withBbox,
                           const bool &bboxOnly){return false;}
    
    virtual Vector getNormal(){return Vector();}
    
    Material* getMaterial() const{return _m;}
    
    void setBbox(const Point &minP, const Point &maxP){
        _bbox.set(minP, maxP);
    }
    
    virtual string getType(){return "surface";};
};

#endif /* Surface_h */
