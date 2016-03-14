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
const double eps = 0.001;

class Bbox{
friend class BVH;
    
private:
    int _id;
    Point _minP, _maxP;
    
public:
    Bbox(): _id(-1), _minP(Point()), _maxP(Point()){}
    
    Bbox(const Point &minP, const Point &maxP, int i){
        _id = i;
        _minP = minP;
        _maxP = maxP;
    }
    
    void setId(int i){_id = i;}
    
    bool intersect(const Ray &r, Intersection &it, bool bboxOnly);
    
    void print();
};

#endif /* Bbox_h */
