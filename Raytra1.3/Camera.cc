//
//  Camera.cc
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Camera.h"

Camera::Camera(){
    _eye = Point();
    _f = 0.0;
    _iw = _ih = 0.0;
    _pw = _ph = 0.0;
    _u = _v = _w = Vector();
    _pixels.resizeErase(0, 0);
}

Camera::Camera(const Point &p, const Vector &dir,
               double d, double iw, double ih,
               int pw, int ph){
    _eye = p;
    _f = d;
    _iw = iw;
    _ih = ih;
    _pw = pw;
    _ph = ph;
    setUvw(dir);
    _pixels.resizeErase(ph, pw);
}

//Set up the camera coordinates
void Camera::setUvw(const Vector &d){
    _w = d * (-1.0);
    _w.normalize();
    if(1 - abs(_w[1]) < 0.0001)
    {
        _u = Vector(1.0, 0.0, 0.0);
        _v = _u.cross(d);
    }
    else{
        Vector up(0.0, 1.0, 0.0);
        _u = d.cross(up);
        _v = _u.cross(d);
    }
    _u.normalize();
    _v.normalize();
}

//Generate ray through the current pixel
Ray Camera::generateRay(double i, double j){
    //Convert pixel coordinates to image plane coordinates
    double l = -_iw/2.0;
    double t = _ih/2.0;
    double U = l + _iw * (i + 0.5) / _pw;
    double V = t - _ih * (j + 0.5) / _ph;
    
    
    Vector dir = _w * (-_f)+ _u * U + _v * V;
    dir.normalize();
    return Ray(_eye, dir);
}

//Render the image
void Camera::render(const vector<Surface*> &objects,
                    const vector<Light*> &lights,
                    const AmbientLight *aLight){
    cout << "render image." << endl;
    Material *m = NULL;
    
    //for each pixel generate a ray through it
    for(int y = 0; y < _ph; y++){
        for(int x = 0; x < _pw; x++){
            Ray r = generateRay(x, y);
            Intersection inter;
            inter.setT1(numeric_limits<double>::max());
            
            //find closest intersecting point
            for(auto obj : objects){
                Intersection tmp = obj->intersect(r);
                if(tmp.intersect()){
                    if(tmp.getT1() < inter.getT1()){
                        inter = tmp;
                        m = obj->getMaterial();
                    }
                }
            }

            //calculate shading
            Vector ret_rgb(0.0, 0.0, 0.0);
            if(inter.intersect()){
                //Normal at intersection
                Vector n = inter.getNormal();
                
                for(auto l : lights){
                    switch (l->getType()){
                            
                        //Point light
                        case 'p':{
                            //Vector from intersection to light position
                            Vector i_l = Vector(inter.getP1(), l->getPos());
                            double maxLen = i_l.getLen();
                            i_l.normalize();
                            
                            if(inShadow(inter.getP1(), i_l, maxLen, objects))
                                continue;
                            
                            //Vector from intersection to camera
                            Vector i_e = r.getDir();
                            i_e *= -1.0;
                            
                            ret_rgb += m->phongShading(i_e, n, i_l, l->getRgb());
                        }
                            break;
                        
                        //Direction light
                        case 'd':{
                            if(inShadow(inter.getP1(), l->getDir(),
                                        numeric_limits<double>::max(), objects))
                                continue;
                            
                            ret_rgb += m->lambertianShading(n, l->getDir(), l->getRgb());
                        }
                            break;
                    }
                }
                
                //ambient shading
//                if(ret_rgb.getLen() < 0.001 && aLight){
//                    ret_rgb += m->ambientShading(aLight->getRgb());
//                }
                
                setPixel(x, y, ret_rgb[0], ret_rgb[1], ret_rgb[2]);
            }
        }
    }
    cout << "finished rendering." << endl;
}

bool Camera::inShadow(const Point &p, const Vector &i_l,
                      const double &maxLen,
                      const vector<Surface*> &objects){
    //ray from intersection to light
    Ray r(p, i_l);
    
    //find if occluded by any object
    for(auto obj : objects){
        Intersection tmp = obj->intersect(r);
        
        //t1 should be less than the distance from intersection to light position
        if(tmp.getT1() > 0.001 && tmp.getT1() < maxLen)
            return true;
    }
    return false;
}

//Write result to output file
void Camera::writeFile(const char outfile[]){
    cout << "writing output image." << endl;
    RgbaOutputFile file (outfile, _pw, _ph, WRITE_RGBA);
    file.setFrameBuffer (&_pixels[0][0], 1, _pw);
    file.writePixels (_ph);
    cout << "done." << endl;
}
