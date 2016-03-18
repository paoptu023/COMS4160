//
//  BVH.cc
//  Raytra
//
//  Created by Qi Wang on 3/4/16.
//  Copy_right © 2016 Wang Qi. All _rights reserved.
//

#include "BVH.h"

BVH::BVH(vector<Surface*> &objs, const int &l,
         const int &r, const int &axis){
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
            int mid = l + (r - l) / 2;
            Sorter compare(axis);
            nth_element(objs.begin() + l, objs.begin() + mid, objs.begin() + r + 1, compare);
            _left = new BVH(objs, l, mid, (axis + 1) % 3);
            _right = new BVH(objs, mid + 1, r, (axis + 1) % 3);
        }
    }
}

void BVH::surround(const vector<Surface*> &objs,
                   const int &l, const int &r){
    double minX, minY, minZ;
    double maxX, maxY, maxZ;
    
    minX = minY = minZ = numeric_limits<double>::max();
    maxX = maxY = maxZ = numeric_limits<double>::min();
    for(int i = l; i <= r; ++i){
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

BVH::~BVH() {
    if (_left)
        delete _left;
    if (_right)
        delete _right;
}