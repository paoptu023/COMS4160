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

class Sorter{
public:
    Sorter(int axis): _axis(axis) {}
    bool operator() (Surface* const a, Surface* const b){
        return a->_bbox._minP[_axis] < b->_bbox._minP[_axis];
    }
    
private:
    int _axis;
};

class BVH : public Surface{
public:
    BVH(): _left(nullptr), _right(nullptr) {}
    
    ~BVH();
    
    BVH(vector<Surface*> &objs, const int &l,
        const int &r, const int &axis);
    
    void surround(const vector<Surface*> &objs,
                  const int &l, const int &r);
    
    bool intersect(const Ray &r, Intersection &it);
    
private:
    Surface *_left;
    Surface *_right;
};

#endif /* BVH_h */
