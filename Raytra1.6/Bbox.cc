//
//  Bbox.cc
//  Raytra
//
//  Created by Qi Wang on 3/4/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Bbox.h"

pair<bool, double> Bbox::intersect(const Ray &r) const{
    pair<bool, double> ret{false, 0.0};
    Point eye = r.getOri();
    
    double dx = 1 / r.getDir()[0];
    double dy = 1 / r.getDir()[1];
    
    double txmin, txmax;
    txmin = (_minP[0] - eye[0]) * dx;
    txmax = (_maxP[0] - eye[0]) * dx;
    if(dx < 0)
        swap(txmin, txmax);
    
    double tymin, tymax;
    tymin = (_minP[1] - eye[1]) * dy;
    tymax = (_maxP[1] - eye[1]) * dy;
    if(dy < 0)
        swap(tymin, tymax);
    
    if(txmin > tymax || tymin > txmax)
        return move(ret);
    
    double dz = 1 / r.getDir()[2];
    double tzmin, tzmax;
    
    tzmin = (_minP[2] - eye[2]) * dz;
    tzmax = (_maxP[2] - eye[2]) * dz;
    if(dz < 0)
        swap(tzmin, tzmax);
    
    double tmin = max(max(txmin, tymin), tzmin);
    double tmax = min(min(txmax, tymax), tzmax);
    
//    if(tmin < tmax){
//        if(bboxOnly){
//            Point p = r.getOri() + r.getDir() * tmin;
//            
//            Vector n;
//            if(tmin - txmin > -eps && tmin - txmin < eps)
//                n = dx > 0? Vector(-1, 0, 0) : Vector(1, 0, 0);
//            else if(tmin - tymin > -eps && tmin - tymin < eps)
//                n = dy > 0? Vector(0, -1, 0) : Vector(0, 1, 0);
//            else if(tmin - tzmin > -eps && tmin - tzmin < eps)
//                n = dz > 0? Vector(0, 0, -1) : Vector(0, 0, 1);
//            else
//                return false;
//            
//            it.set(tmin, p, n);
//        }
//        it.setT1(tmin);
    ret.first = tmin < tmax;
    ret.second = tmin;
    return move(ret);
}

void Bbox::print(){
    cout << "min Point: ";
    _minP.print();
    cout << "max Point: ";
    _maxP.print();
}
