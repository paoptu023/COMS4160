//
//  BVH.cc
//  Raytra
//
//  Created by Qi Wang on 3/4/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "BVH.h"

static bool compareX(Surface *a, Surface *b){
    return a->getMaxP()[0] < b->getMaxP()[0];
}

static bool compareY(Surface *a, Surface *b){
    return a->getMaxP()[1] < b->getMaxP()[1];
}

static bool compareZ(Surface *a, Surface *b){
    return a->getMaxP()[2] < b->getMaxP()[2];
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
            int mid = l + (r - l) / 2;
            switch (axis) {
                case 0:
                    nth_element(objects.begin() + l, objects.begin() + mid,
                                objects.begin() + r + 1, compareX);
                    break;

                case 1:
                    nth_element(objects.begin() + l, objects.begin() + mid,
                                objects.begin() + r + 1, compareY);
                    break;

                case 2:
                    nth_element(objects.begin() + l, objects.begin() + mid,
                                objects.begin() + r + 1, compareZ);
                    break;
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
    Intersection tmp;
    //leaf node
    if(right == NULL){
        if(left->intersect(r, it, bboxOnly) && it.getT1() > 0.0001)
            return true;
    }
    else if(_bbox.intersect(r, tmp, bboxOnly) && tmp.getT1() < it.getT1()){
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
    else if(_bbox.intersect(r, it, bboxOnly)){
        bool hit = left->intersect(r, it, bboxOnly) && it.getT1() > 0.0001;
        if(hit)
            return true;
        
        hit = right->intersect(r, it, bboxOnly) && it.getT1() > 0.0001;
        if(hit)
            return true;
    }
    return false;
}