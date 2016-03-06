//
//  AmbientLight.h
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef AmbientLight_h
#define AmbientLight_h

#include <vector>
#include "Point.h"
using namespace std;

class AmbientLight{
private:
    vector<double> _rgb;
    
public:
    //Default Constructor
    AmbientLight(): _rgb({0.0, 0.0, 0.0}) {}
    
    //Initialization
    void initial(double r, double g, double b){_rgb = {r, g, b};}
    
    //Access private elements
    vector<double> getRgb() const{return _rgb;}
    
    void print(){
        cout << "RGB: " << _rgb[0] << " " << _rgb[1] << " " << _rgb[2] << endl;
    }
};

#endif /* AmbientLight_h */
