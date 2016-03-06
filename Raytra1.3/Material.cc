//
//  Material.cc
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Material.h"

Material::Material(){
    _diffuse = _specular = _idealSpec = Vector(0.0, 0.0, 0.0);
    _r = 0.0;
}

Material::Material(double dr, double dg, double db,
                   double sr, double sg, double sb,
                   double r, double ir, double ig, double ib){
    _diffuse = Vector(dr, dg, db);
    _specular = Vector(sr, sg, sb);
    _idealSpec = Vector(ir, ig, ib);
    _r = r;
}

//Blinn-Phong shading
Vector Material::phongShading(const Vector &i_e, const Vector &n,
                              const Vector &i_l, const Vector &l_Rgb){
    Vector rgb(0.0, 0.0, 0.0);
    
    Vector h = i_e + i_l;
    h.normalize();
    
    double cosnl = max(0.0, n.dot(i_l));
    double cosnh = max(0.0, n.dot(h));
    
    rgb += (_diffuse * l_Rgb) * cosnl + (_specular * l_Rgb) * pow(cosnh, _r);
    return rgb;
}

//Diffuse shading
Vector Material::lambertianShading(const Vector &n, const Vector &l,
                                   const Vector &l_Rgb){
    Vector rgb(0.0, 0.0, 0.0);
    
    double cosnl = max(0.0, n.dot(l));
    rgb += (_diffuse * l_Rgb) * cosnl;
    return rgb;
}

//Ambient shading
Vector Material::ambientShading(const Vector &l_Rgb){
    return Vector(_diffuse[0] * l_Rgb[0], _diffuse[1] * l_Rgb[1], _diffuse[2] * l_Rgb[2]) * 0.005;
}