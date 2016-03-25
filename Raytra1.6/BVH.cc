//
//  BVH.cc
//  Raytra
//
//  Created by Qi Wang on 3/4/16.
//  Copy_right © 2016 Wang Qi. All _rights reserved.
//

#include "BVH.h"

BVH::BVH(vector<Surface*> &objs, const int l,
         const int r, const int axis){
    if(l == r){
        _left = objs[l];
        _right = nullptr;
    }
    else if(l < r){
        surround(objs, l, r);
        if(r == l + 1){
            _left = objs[l];
            _right = objs[r];
        }
        else{
            int mid = getVolumeMid(objs, l, r);
            Sorter compare(axis);
            nth_element(objs.begin() + l, objs.begin() + mid, objs.begin() + r + 1, compare);
//            sort(objs.begin() + l, objs.begin() + r + 1, compare);
            _left = new BVH(objs, l, mid, (axis + 1) % 3);
            _right = new BVH(objs, mid + 1, r, (axis + 1) % 3);
        }
    }
}

void BVH::surround(const vector<Surface*> &objs,
                   const int l, const int r){
    double minX = objs[l]->_bbox._minP[0];
    double minY = objs[l]->_bbox._minP[1];
    double minZ = objs[l]->_bbox._minP[2];
    
    double maxX = objs[l]->_bbox._maxP[0];
    double maxY = objs[l]->_bbox._maxP[1];
    double maxZ = objs[l]->_bbox._maxP[2];
    for(int i = l + 1; i <= r; ++i){
        minX = min(minX, objs[i]->_bbox._minP[0]);
        minY = min(minY, objs[i]->_bbox._minP[1]);
        minZ = min(minZ, objs[i]->_bbox._minP[2]);
        
        maxX = max(maxX, objs[i]->_bbox._maxP[0]);
        maxY = max(maxY, objs[i]->_bbox._maxP[1]);
        maxZ = max(maxZ, objs[i]->_bbox._maxP[2]);
    }
    
    _bbox = Bbox(Point(minX - eps, minY - eps, minZ - eps),
                 Point(maxX + eps, maxY + eps, maxZ + eps));
}

bool BVH::intersect(const Ray &r, Intersection &it){
    //leaf node
    if(!_right){
        if(_left->intersect(r, it))
            return true;
    }
    else{
        pair<bool, double> ret = _bbox.intersect(r);
        if(ret.first && ret.second < it.getT1()){
            bool lHit = _left->intersect(r, it);
            bool rHit = _right->intersect(r, it);
            if(lHit || rHit)
                return true;
        }
    }
    return false;
}

int BVH::getVolumeMid(const vector<Surface*> &objects,
                         const int l, const int r) {
    int start = l;
    int end = r;
    int mid = l;
    
    // Binary search
    while (start < end) {
        mid = start + (end - start) / 2;
        float left = computeVolume(objects, start, mid);
        float right = computeVolume(objects, mid, end);
        
        // update begin, end, mid
        if (left >= right)
            end = mid;
        else
            start = mid + 1;
    }
    return mid;
}

double BVH::computeVolume(const vector<Surface*> &objs,
                          const int l, const int r){
    double minX = objs[l]->_bbox._minP[0];
    double minY = objs[l]->_bbox._minP[1];
    double minZ = objs[l]->_bbox._minP[2];
    
    double maxX = objs[l]->_bbox._maxP[0];
    double maxY = objs[l]->_bbox._maxP[1];
    double maxZ = objs[l]->_bbox._maxP[2];
    for(int i = l + 1; i <= r; ++i){
        minX = min(minX, objs[i]->_bbox._minP[0]);
        minY = min(minY, objs[i]->_bbox._minP[1]);
        minZ = min(minZ, objs[i]->_bbox._minP[2]);
        
        maxX = max(maxX, objs[i]->_bbox._maxP[0]);
        maxY = max(maxY, objs[i]->_bbox._maxP[1]);
        maxZ = max(maxZ, objs[i]->_bbox._maxP[2]);
    }
    return (maxX - minX) * (maxY - minY) * (maxZ - minZ);
}