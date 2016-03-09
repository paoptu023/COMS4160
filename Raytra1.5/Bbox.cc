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
    
    if(tmax > tmin){
        double px = r.getOri()[0] + r.getDir()[0] * tmin;
        double py = r.getOri()[1] + r.getDir()[1] * tmin;
        double pz = r.getOri()[2] + r.getDir()[2] * tmin;
        
        double tmpX_min = px - _minP[0];
        double tmpX_max = px - _maxP[0];
        double tmpY_min = py - _minP[1];
        double tmpY_max = py - _maxP[1];
        double tmpZ_min = pz - _minP[2];
        double tmpZ_max = pz - _maxP[2];

        
        Vector n;
        if(tmpX_min > -limit && tmpX_min < limit)
            n = Vector(-1, 0, 0);
        else if(tmpX_max > -limit && tmpX_max < limit)
            n = Vector(1, 0, 0);
        else if(tmpY_min > -limit && tmpY_min < limit)
            n = Vector(0, -1, 0);
        else if(tmpY_max > -limit && tmpY_max < limit)
            n = Vector(0, 1, 0);
        else if(tmpZ_min > -limit && tmpZ_min < limit)
            n = Vector(0, 0, -1);
        else if(tmpZ_max > -limit && tmpZ_max < limit)
            n = Vector(0, 0, 1);
        else
            return false;
        
        it.set(tmin, Point(px, py, pz), n);
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
