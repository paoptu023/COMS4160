//
//  Bbox.cc
//  Raytra
//
//  Created by Qi Wang on 3/4/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Bbox.h"

bool Bbox::intersect(const Ray &r, Intersection &it){
    Point eye = r.getOri();
    
    double dx = 1 / r.getDir()[0];
    double dy = 1 / r.getDir()[1];
    
    double txmin, txmax, tymin, tymax;
    txmin = (_minP[0] - eye[0]) * dx;
    txmax = (_maxP[0] - eye[0]) * dx;
    if(dx < 0)
        swap(txmin, txmax);
    
    tymin = (_minP[1] - eye[1]) * dy;
    tymax = (_maxP[1] - eye[1]) * dy;
    if(dy < 0)
        swap(tymin, tymax);
    
    if(txmin > tymax || tymin > txmax)
        return false;
    
    double tmin = max(txmin, tymin);
    double tmax = min(txmax, tymax);
    
    double dz = 1 / r.getDir()[2];
    double tzmin, tzmax;
    
    tzmin = (_minP[2] - eye[2]) * dz;
    tzmax = (_maxP[2] - eye[2]) * dz;
    if(dz < 0)
        swap(tzmin, tzmax);
    
    if(tmin > tzmax || tzmin > tmax)
        return false;
    
    tmin = max(tmin, tzmin);
    tmax = min(tmax, tzmax);
    
    if(tmax > 0){
        Point p1 = r.getOri() + r.getDir() * tmin;
        Point p2 = r.getOri() + r.getDir() * tmax;
        Vector n;
        
        double tmpX_min = p1[0] - _minP[0];
        double tmpX_max = p1[0] - _maxP[0];
        double tmpY_min = p1[1] - _minP[1];
        double tmpY_max = p1[1] - _maxP[1];
        double tmpZ_min = p1[2] - _minP[2];
        
        
        if(tmpX_min >= -0.001 && tmpX_min <= 0.001)
            n = Vector(-1, 0, 0);
        else if(tmpX_max >= -0.001 && tmpX_max <= 0.001)
            n = Vector(1, 0, 0);
        else if(tmpY_min >= -0.001 && tmpY_min <= 0.001)
            n = Vector(0, -1, 0);
        else if(tmpY_max >= -0.001 && tmpY_max <= 0.001)
            n = Vector(0, 1, 0);
        else if(tmpZ_min >= -0.001 && tmpZ_min <= 0.001)
            n = Vector(0, 0, -1);
        else
            n = Vector(0, 0, 1);
        
        it.set(tmin, tmax, p1, p2, n);
        if(_id != -1)
            it.setId(_id);
        
        return true;
    }
    return false;
}

void Bbox::print(){
    cout << "min Point: ";
    _minP.print();
    cout << "max Point: ";
    _maxP.print();
}
