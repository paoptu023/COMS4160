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
#include "Intersection.h"

class Surface{
protected:
    Material *_m;
    
public:
    Surface(): _m(NULL) {}
    
    virtual bool intersect(const Ray &r, Intersection &it) {return false;}
    
    virtual Vector getNormal() {return Vector();}
    
    virtual Material* getMaterial() const{return _m;}
    
    virtual string getType(){return "surface";};
};

#endif /* Surface_h */
