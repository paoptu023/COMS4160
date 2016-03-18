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
#include "Point.h"
#include "Ray.h"

class Bbox{
friend class BVH;
friend class Sorter;
    
public:
    Bbox(): _minP(Point()), _maxP(Point()) {}
    
    Bbox(const Point &minP,
         const Point &maxP): _minP(minP), _maxP(maxP) {}
    
    pair<bool, double> intersect(const Ray &r) const;
    
    void print();
    
private:
    Point _minP, _maxP;
};

#endif /* Bbox_h */
