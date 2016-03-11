//
//  BVH.cc
//  Raytra
//
//  Created by Qi Wang on 3/4/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "BVH.h"

void BVH::quickSort(vector<Surface*> &objs, int l, int r, int axis){
    if(l < r){
        int pivot = objs[r]->_max[axis];
        int p = partition(objs, l, r - 1, pivot, axis);
        swap(objs[++p], objs[r]);
        quickSort(objs, l, p - 1, axis);
        quickSort(objs, p + 1, r, axis);
    }
}

//partial sort
int BVH::partition(vector<Surface*> &objs, int l, int r, int pivot, int axis){
    int i = l - 1;
    for(int j = l; j <= r; ++j){
        if(objs[j]->_max[axis] < pivot)
            swap(objs[++i], objs[j]);
    }
    return i;
}

BVH::BVH(vector<Surface*> &objects, int l, int r, int axis){
    if(l == r){
        left = objects[l];
        left->_bbox.setId(l);
        right = NULL;
    }
    else if(l < r){
        surround(objects, l, r);
        if(r == l + 1){
            left = objects[l];
            left->_bbox.setId(l);
            right = objects[r];
            right->_bbox.setId(r);
        }
        else{
            //partition by volume
            int pivot = (_bbox._minP[axis] + _bbox._maxP[axis]) / 2;
            int mid = partition(objects, l, r, pivot, axis);
            
            //objects are close in space, so partition by number instead
            if(mid == l-1 || mid == r){
                quickSort(objects, l, r, axis);
                mid = l + (r - l) / 2;
            }
            
            left = new BVH(objects, l, mid, (axis + 1) % 3);
            right = new BVH(objects, mid + 1, r, (axis + 1) % 3);
        }
    }
}

void BVH::surround(const vector<Surface*> objs, int l, int r){
    double minX, minY, minZ;
    double maxX, maxY, maxZ;
    
    minX = minY = minZ = numeric_limits<double>::max();
    maxX = maxY = maxZ = numeric_limits<double>::min();
    for(int i = l; i <= r; ++i){
        minX = min(minX, objs[i]->_min[0]);
        minY = min(minY, objs[i]->_min[1]);
        minZ = min(minZ, objs[i]->_min[2]);
        
        maxX = max(maxX, objs[i]->_max[0]);
        maxY = max(maxY, objs[i]->_max[1]);
        maxZ = max(maxZ, objs[i]->_max[2]);
    }
    
    _bbox = Bbox(Point(minX - e, minY - e, minZ - e), Point(maxX + e, maxY + e, maxZ + e), -1);
}

bool BVH::intersect(const Ray &r, Intersection &it, bool bboxOnly){
    //leaf node
    if(right == NULL){
        if(left->intersect(r, it, bboxOnly) && it.getT1() > 0.0001)
            return true;
    }
    else if(_bbox.intersect(r, it)){
        Intersection lIt, rIt;
        bool lHit = left->intersect(r, lIt, bboxOnly) && lIt.getT1() > 0.0001;
        bool rHit = right->intersect(r, rIt, bboxOnly) && rIt.getT1() > 0.0001;
        if(!lHit && !rHit)
            return false;
        else{
            //find closest intersection
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

bool BVH::shadowTest(const Ray &r, Intersection &it, bool bboxOnly){
    //leaf node
    if(right == NULL){
        if(left->intersect(r, it, bboxOnly) && it.getT1() > 0.0001)
            return true;
    }
    else if(_bbox.intersect(r, it)){
        bool hit = left->intersect(r, it, bboxOnly) && it.getT1() > 0.0001;
        if(hit)
            return true;
        
        hit = right->intersect(r, it, bboxOnly) && it.getT1() > 0.0001;
        if(hit)
            return true;
    }
    return false;
}