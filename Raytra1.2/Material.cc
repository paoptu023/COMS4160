//
//  Material.cc
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Material.h"

Material::Material(){
    _diffuse = {0.0, 0.0, 0.0};
    _specular = {0.0, 0.0, 0.0};
    _idealSpec = {0.0, 0.0, 0.0};
    _r = 0.0;
}

void Material::setMaterial(double dr, double dg, double db,
                   double sr, double sg, double sb,
                   double r, double ir, double ig, double ib){
    _diffuse = {dr, dg, db};
    _specular = {sr, sg, sb};
    _idealSpec = {ir, ig, ib};
    _r = r;
}