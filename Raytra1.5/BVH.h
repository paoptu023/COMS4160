//
//  BVH.h
//  Raytra
//
//  Created by Qi Wang on 3/4/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef BVH_h
#define BVH_h
#include "Surface.h"
#include <vector>
#include <cmath>

class BVH : public Surface{
private:
    Surface *_left;
    Surface *_right;
    
public:
    BVH(): _left(NULL), _right(NULL) {}
    
    BVH(vector<Surface*> &objects, int l, int r, int axis);
    
    void surround(const vector<Surface*> objects, int l, int r);
    
    bool intersect(const Ray &r, Intersection &it,
                   const bool &withBbox,
                   const bool &bboxOnly);
    
    virtual string getType(){return "BVH";};
};

#endif /* BVH_h */
