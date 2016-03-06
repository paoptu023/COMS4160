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
    Bbox(): _minP(Point()), _maxP(Point()), _id(-1) {}
    
    void set(const Point &minP, const Point &maxP){
        _minP = minP;
        _maxP = maxP;
    }
    
    void setId(const int ii){_id = ii;}
    
    Point getMin() const{return move(_minP);}
    Point getMax() const{return move(_maxP);}
    
    bool intersect(const Ray &r, Intersection &it);
    
    void print();
};

#endif /* Bbox_h */
