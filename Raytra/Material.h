//
//  Material.h
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Material_h
#define Material_h

#include "Vector.h"
#include "Intersection.h"
#include "Light.h"
#include <cmath>
using namespace std;

class Material{
private:
    Vector _diffuse;      //Diffuse components
    Vector _specular;     //Specular components
    Vector _idealSpec;    //Ideal specular components
    double _r;            //Phong exponent
    
    double _ni;           //Refraction index
    Vector _attenuate;    //Attenuation constant
    
public:
    Material();
    
    Material(double dr, double dg, double db,
             double sr, double sg, double sb,
             double r, double ir, double ig, double ib);
    
    void setRefraction(double ni, double ar, double ag, double ab);
    
    //Blinn-Phong shading
    Vector phongShading(const Vector &i_e, const Vector &n,
                        const Vector &i_l, const Vector &l_rgb);
    
    //Diffuse shading
    Vector lambertianShading(const Vector &n, const Vector &l,
                             const Vector &l_Rgb);
    
    //Ambient shading
    Vector ambientShading(const Vector &l_Rgb);
    
    Vector getIdealSpec() const{return _idealSpec;}
    
    double getRefIndex() const{return _ni;}
    
    Vector getAttenuate() const{return _attenuate;}
};

#endif /* Material_h */
