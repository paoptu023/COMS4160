//
//  Light.h
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Light_h
#define Light_h

#include <vector>
#include "Point.h"
using namespace std;

class PointLight{
private:
    Point _pos;
    vector<double> _rgb;
    
public:
    //Default Constructor
    PointLight(): _pos(Point()), _rgb({0.0, 0.0, 0.0}) {}
    //Constructor
    PointLight(const Point &p, double r, double g, double b): _pos(p), _rgb({r, g, b}) {}
    
    //Access private elements
    Point getPos() const{return _pos;}
    vector<double> getRgb() const{return _rgb;}
    
    void print(){
        cout << "RGB: " << _rgb[0] << " " << _rgb[1] << " " << _rgb[2] << endl;
    }
};

#endif /* Light_h */
