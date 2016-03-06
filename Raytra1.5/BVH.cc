//
//  BVH.cc
//  Raytra
//
//  Created by Qi Wang on 3/4/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "BVH.h"
static bool compare(const Surface *a, const Surface *b){
    Point midA = (a->_bbox.getMin() + a->_bbox.getMax()) / 2;
    Point midB = (b->_bbox.getMin() + b->_bbox.getMax()) / 2;
    return midA[0] < midB[0];
}

BVH::BVH(vector<Surface*> &objects, int l, int r, int axis){
    if(l == r){
        _left = objects[l];
        _right = NULL;
        _bbox = objects[l]->_bbox;
        _bbox.setId(l);
    }
    else if(l < r){
        surround(objects, l, r);
        if(r == l + 1){
            _left = new BVH(objects, l, l, axis);
            _right = new BVH(objects, r, r, axis);
        }
        else{
            int mid = (r - l + 1)/2;
            nth_element(objects.begin() + l, objects.begin() + mid, objects.end(), compare);
            
            _left = new BVH(objects, l, l + mid, (axis + 1)%3);
            _right = new BVH(objects, l + mid + 1, r, (axis + 1)%3);
        }
    }
}

void BVH::surround(const vector<Surface*> objects, int l, int r){
    double minX, minY, minZ;
    double maxX, maxY, maxZ;
    
    minX = minY = minZ = numeric_limits<double>::max();
    maxX = maxY = maxZ = numeric_limits<double>::min();
    for(int i = l; i <= r; ++i){
        minX = min(minX, objects[i]->_bbox._minP[0]);
        minY = min(minY, objects[i]->_bbox._minP[1]);
        minZ = min(minZ, objects[i]->_bbox._minP[2]);
        
        maxX = max(maxX, objects[i]->_bbox._maxP[0]);
        maxY = max(maxY, objects[i]->_bbox._maxP[1]);
        maxZ = max(maxZ, objects[i]->_bbox._maxP[2]);
    }
    
    _bbox.set(Point(minX, minY, minZ), Point(maxX, maxY, maxZ));
}

bool BVH::intersect(const Ray &r, Intersection &it,
                    const bool &withBbox,
                    const bool &bboxOnly){
    if(_bbox.intersect(r, it)){
        if(_right == NULL){
            if(_left->intersect(r, it, withBbox, bboxOnly) && it.getT1() > 0.0001)
               return true;
            else
               return false;
        }
        
        Intersection lIt, rIt;
        bool lHit = _left->intersect(r, lIt, withBbox, bboxOnly);
        bool rHit = _right->intersect(r, rIt, withBbox, bboxOnly);
        if(!lHit && !rHit)
            return false;
        else{
            if (lHit && rHit){
                if(lIt.getT1() < rIt.getT1())
                    it = lIt;
                else
                    it = rIt;
            }
            else if(lHit)
                it = lIt;
            else
                it = rIt;
            
            return true;
        }
    }
    return false;
}