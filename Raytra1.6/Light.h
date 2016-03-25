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
#include <vector>
#include <time.h>
using namespace std;

class Light{
public:
    Light(): _rgb(Vector(0.0, 0.0, 0.0)) {}
    
    virtual ~Light() {}
    
    Vector getRgb() const{return _rgb;}
    
    void print(){
        cout << "RGB: " << _rgb[0] << " " << _rgb[1] << " " << _rgb[2] << endl;
    }
    
    virtual int getType() const{return 0;}
    
protected:
    Vector _rgb;
};


class PointLight : public Light{
public:
    PointLight(): _pos(Point()) {}
    
    PointLight(const Point &p, double r, double g, double b);
    
    int getType() const{return 1;}
    
    Point getPos() const{return _pos;}
    
private:
    Point _pos;
};

class AreaLight : public Light{
public:
    AreaLight(){
        _corner = Point();
        _dir = _u = _v = Vector();
        _len = 0.0;
    }
    
    AreaLight(double x, double y, double z,
              const Vector &v, const Vector &u,
              double len, double r, double g, double b);
    
    void generateSample(const int s_num, vector<Point> &samples);
    
    Vector getDir() const{return _dir;}
    
    Point getCenter() const{return move(_corner + (_u + _v) * 0.5 * _len);}
    
    int getType() const{return 2;}
    
private:
    Point _corner;
    Vector _dir, _u, _v;
    double _len;
};

class AmbientLight : public Light{
public:
    AmbientLight(double r, double g, double b){
        _rgb = Vector(r, g, b);
    }
    
    int getType() const{return 3;}
};

class DirectionLight : public Light{
public:
    DirectionLight(): _dir(Vector()) {}
    
    DirectionLight(double x, double y, double z, double r, double g, double b);
    
    int getType() const{return 4;}
    
    Vector getDir() const{return _dir;}
    
private:
    Vector _dir;
};

#endif /* Light_h */
