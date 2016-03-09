//
//  Bbox.h
//  Raytra
//
//  Created by Qi Wang on 3/4/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Bbox_h
#define Bbox_h

#include "Intersection.h"

class Bbox{
friend class BVH;
    
private:
    Point _minP, _maxP;
    int _id;
    
public:
    Bbox(): _minP(Point()), _maxP(Point()), _id(-1){}
    
    Bbox(const Point &minP, const Point &maxP, int i){
        _minP = minP;
        _maxP = maxP;
        _id = i;
    }
    
    void setId(int i){_id = i;}
    
    bool intersect(const Ray &r, Intersection &it);
    
    void print();
};

#endif /* Bbox_h */
