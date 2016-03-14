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
    
public:
    Bbox(): _minP(Point()), _maxP(Point()){}
    
    Bbox(const Point &minP, const Point &maxP, int i){
        _minP = minP;
        _maxP = maxP;
    }
    
    bool intersect(const Ray &r, Intersection &it) const;
    
    void print();
};

#endif /* Bbox_h */
