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
private:
    Material _m;
    
public:
    Surface(): _m(Material()) {}
    
    //Set material
    void setMaterial(const Material &m){_m = m;}
    
    //Check intersection
    virtual void intersect(const Ray &r, Intersection &i) {}
    
    //Calculate normal
    virtual Vector getNormal(const Point &p) {return Vector();}
    
    //Get material
    virtual Material getMaterial() const{return _m;}
    
    virtual void getType(){cout << "surface" << endl;};
};

#endif /* Surface_h */
