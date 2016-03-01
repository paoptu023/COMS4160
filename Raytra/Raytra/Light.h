//
//  Light.h
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Light_h
#define Light_h

#include "Point.h"
using namespace std;

class Light{
protected:
    Vector _rgb;
    
public:
    Light(): _rgb(Vector(0.0, 0.0, 0.0)) {}
    
    virtual Vector getRgb() const{return move(_rgb);}
    
    virtual void print(){
        cout << "RGB: " << _rgb[0] << " " << _rgb[1] << " " << _rgb[2] << endl;
    }
    
    virtual void setRgb(double k){_rgb *= k;}
    
    virtual char getType() const{return 'l';}
    
    virtual Point getPos() const{return Point();}
    
    virtual Vector getDir() const{return Vector();}
};


class PointLight : public Light{
private:
    Point _pos;
    
public:
    PointLight(): _pos(Point()) {}

    PointLight(const Point &p, double r, double g, double b){
        _pos = p;
        _rgb = Vector(r, g, b);
    }
    
    char getType() const{return 'p';}
    
    Point getPos() const{return move(_pos);}
};


class AmbientLight : public Light{
public:
    AmbientLight(double r, double g, double b){
        _rgb = Vector(r, g, b);
    }
    
    char getType() const{return 'a';}
};

class DirectionLight : public Light{
private:
    Vector _dir;
    
public:
    DirectionLight(): _dir(Vector()) {}
    
    DirectionLight(double x, double y, double z, double r, double g, double b){
        _dir = Vector(x, y, z);
        _dir.normalize();
        _rgb = Vector(r, g, b);
    }
    
    char getType() const{return 'd';}
    
    Vector getDir() const{return move(_dir);}
};

#endif /* Light_h */
