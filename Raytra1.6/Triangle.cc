//
//  Triangle.cc
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Triangle.h"

Triangle::Triangle(){
    _p1 = _p2 = _p3 = Point();
    _n = Vector();
    _a = _b = _c = _d = _e = _f = 0.0;
}

Triangle::Triangle(const double x1, const double y1, const double z1,
                   const double x2, const double y2, const double z2,
                   const double x3, const double y3, const double z3, Material *m){
    _p1 = Point(x1, y1, z1);
    _p2 = Point(x2, y2, z2);
    _p3 = Point(x3, y3, z3);
    
    _a = x1 - x2;
    _b = y1 - y2;
    _c = z1 - z2;
    _d = x1 - x3;
    _e = y1 - y3;
    _f = z1 - z3;
    
    //Calculate normal
    Vector p1_p2 = Vector(_p1, _p2);
    Vector p1_p3 = Vector(_p1, _p3);
    _n = p1_p2.cross(p1_p3);
    _n.normalize();
    _m = m;
    
    float minX = min(x1, min(x2, x3));
    float maxX = max(x1, max(x2, x3));
    float minY = min(y1, min(y2, y3));
    float maxY = max(y1, max(y2, y3));
    float minZ = min(z1, min(z2, z3));
    float maxZ = max(z1, max(z2, z3));
    
    Point minP(minX - eps, minY - eps, minZ - eps);
    Point maxP(maxX + eps, maxY + eps, maxZ + eps);
    _bbox = Bbox(minP, maxP);
}

bool Triangle::intersect(const Ray &r, Intersection &it){
    pair<bool, double> ret = _bbox.intersect(r);
    if(!ret.first || ret.second > it.getT1())
        return false;
    
    double g = r.getDir()._xyz[0];
    double h = r.getDir()._xyz[1];
    double i = r.getDir()._xyz[2];
    
    double ei_hf = _e * i - h * _f;
    double gf_di = g * _f - _d * i;
    double dh_eg = _d * h - _e * g;
    
    double M = _a * ei_hf + _b * gf_di + _c * dh_eg;
    
    if(M == 0)
        return false;
    else{
        double j = _p1._xyz[0] - r.getOri()._xyz[0];
        double k = _p1._xyz[1] - r.getOri()._xyz[1];
        double l = _p1._xyz[2] - r.getOri()._xyz[2];
        
        double ak_jb = _a * k - j * _b;
        double jc_al = j * _c - _a * l;
        double bl_kc = _b * l - k * _c;
        
        double t = -(_f * ak_jb + _e * jc_al + _d * bl_kc)/M;
        if(t < 0.0001 || t > it.getT1())
            return false;
        
        double gamma = (i * ak_jb + h * jc_al + g * bl_kc)/M;
        if(gamma < 0 || gamma > 1)
            return false;
        
        double beta = (j * ei_hf + k * gf_di + l * dh_eg)/M;
        if(beta < 0 || beta > 1 - gamma)
            return false;

        it.set(t, _n, _m);
        return true;
    }
}


