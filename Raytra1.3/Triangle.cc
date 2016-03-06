//
//  Triangle.cc
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Triangle.h"

Triangle::Triangle(){
    _m = NULL;
    _p1 = _p2 = _p3 = Point();
    _n = Vector();
}

Triangle::Triangle(double x1, double y1, double z1,
                   double x2, double y2, double z2,
                   double x3, double y3, double z3, Material *m){
    _p1 = Point(x1, y1, z1);
    _p2 = Point(x2, y2, z2);
    _p3 = Point(x3, y3, z3);
    
    //Calculate normal
    Vector p1_p2 = Vector(_p1, _p2);
    Vector p1_p3 = Vector(_p1, _p3);
    _n = p1_p2.cross(p1_p3);
    _n.normalize();

    _m = m;
}

Intersection Triangle::intersect(const Ray &r){
    //matrix A
    double a = _p1[0] - _p2[0];
    double d = _p1[0] - _p3[0];
    double g = r.getDir()[0];
    
    double b = _p1[1] - _p2[1];
    double e = _p1[1] - _p3[1];
    double h = r.getDir()[1];
    
    double c = _p1[2] - _p2[2];
    double f = _p1[2] - _p3[2];
    double i = r.getDir()[2];
    
    double ei_hf = e * i - h * f;
    double gf_di = g * f - d * i;
    double dh_eg = d * h - e * g;
    
    double M = a * ei_hf + b * gf_di + c * dh_eg;
    Intersection inter;
    inter.setNormal(_n);
    
    if(M == 0)
        return inter;
    else{
        double j = _p1[0] - r.getOri()[0];
        double k = _p1[1] - r.getOri()[1];
        double l = _p1[2] - r.getOri()[2];
        
        double ak_jb = a * k - j * b;
        double jc_al = j * c - a * l;
        double bl_kc = b * l - k * c;
        
        double t = -(f * ak_jb + e * jc_al + d * bl_kc)/M;
        double gamma = (i * ak_jb + h * jc_al + g * bl_kc)/M;
        double beta = (j * ei_hf + k * gf_di + l * dh_eg)/M;
        
        //intersection with edges
        if(t >= 0 && gamma >= 0 && gamma <= 1 && beta >= 0 && beta <= 1 - gamma)
            inter.initial(t, t, r);
        return inter;
    }
}

