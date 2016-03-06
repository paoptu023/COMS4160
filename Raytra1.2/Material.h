//
//  Material.h
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Material_h
#define Material_h

#include <vector>
using namespace std;

class Material{
private:
    vector<double> _diffuse;    //Diffuse components
    vector<double> _specular;   //Specular components
    vector<double> _idealSpec;  //Ideal specular components
    double _r;                  //Phong exponent
    
public:
    //Default constructor
    Material();
    
    //Set parameters
    void setMaterial(double dr, double dg, double db,
             double sr, double sg, double sb,
             double r, double ir, double ig, double ib);
    
    //Access private elements
    vector<double> getDiffuse() const{return _diffuse;}
    vector<double> getSpecular() const{return _specular;}
    vector<double> getIdeal() const{return _idealSpec;}
    double getPhong() const{return _r;}
};

#endif /* Material_h */
