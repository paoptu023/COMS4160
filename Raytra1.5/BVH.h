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
#include <algorithm>

class BVH : public Surface{
public:
    Surface *left;
    Surface *right;
    
    BVH(): left(NULL), right(NULL) {}
    
    BVH(vector<Surface*> &objects, int l, int r, int axis);
    
    void surround(const vector<Surface*> objects, int l, int r);
    
    bool intersect(const Ray &r, Intersection &it, bool bboxOnly);
    
    int partition(vector<Surface*> &objs, int l, int r, int pivot, int axis);
    
    void quickSort(vector<Surface*> &objs, int l, int r, int axis);
};

#endif /* BVH_h */
