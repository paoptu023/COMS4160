//
//  AreaLight.cc
//  Raytra
//
//  Created by Qi Wang on 3/14/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Light.h"

PointLight::PointLight(const Point &p, double r,
                       double g, double b){
    _pos = p;
    _rgb = Vector(r, g, b);
}

AreaLight::AreaLight(double x, double y, double z,
                     const Vector &v, const Vector &u,
                     double len, double r, double g, double b){
    _dir = v; _dir.normalize();
    _u = u; _u.normalize();
    
    //_v is _u cross pointing direction
    _v = _u.cross(_dir);
    _v.normalize();
    
    _corner = Point(x, y, z) - (_u + _v) * len * 0.5;

    _len = len;
    _rgb = Vector(r, g, b);
}

void AreaLight::generateSample(const int s_num, vector<Point> &samples){
    for(int i = 0; i < s_num; ++i){
        for(int j = 0; j < s_num; ++j){
            Point p = _corner + _u * _len * (i + (double)rand()/RAND_MAX) / s_num +
                             _v * _len * (j + (double)rand()/RAND_MAX) / s_num;
            samples.push_back(p);
        }
    }
    
    //shuffle sample array
//    for(int i = s_num * s_num; i > 0; --i){
//        int id1 = rand() % i;
//        int id2 = rand() % i;
//        swap(samples[id1], samples[id2]);
//    }
}

DirectionLight::DirectionLight(double x, double y, double z, double r, double g, double b){
    _dir = Vector(x, y, z);
    _dir.normalize();
    _rgb = Vector(r, g, b);
}