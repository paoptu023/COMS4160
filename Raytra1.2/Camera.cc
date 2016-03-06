//
//  Camera.cc
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Camera.h"
#include <unordered_set>

//Default constructor
Camera::Camera(){
    _eye = Point();
    _f = 0.0;
    _iw = _ih = 0.0;
    _pw = _ph = 0.0;
    _u = _v = _w = Vector();
    _pixels.resizeErase(0, 0);
}

void Camera::initial(const Point &p, const Vector &dir,
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
    Vector up(0.0, 1.0, 0.0);
    Vector tmp = d;
    if(tmp == up)
    {
        cout << "Camera parallel to up direction" << endl;
        exit(-1);
    }
    
    _u = d.cross(up);
    _v = _u.cross(d);
    _w = d * (-1.0);
    _u.normalize();
    _v.normalize();
    _w.normalize();
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
                    const AmbientLight &aLight,
                    const vector<PointLight*> &pLights){
    cout << "render image." << endl;
    unordered_set<int> mySet;
    
    for(int y = 0; y < _ph; y++){
        for(int x = 0; x < _pw; x++){
            Ray r = generateRay(x, y);
            Rgba & px = _pixels[y][x]; //gets current pixel
            px.a = 1;
            px.r = 0;
            px.g = 0;
            px.b = 0;
            Intersection inter;
            Surface *closestObj = NULL;
            
            //find closest intersecting point
            for(auto obj : objects){
                Intersection tmp;
                obj->intersect(r, tmp);
                if(tmp.intersect()){
                    if(inter.getT1() == 0.0 || tmp.getT1() < inter.getT1()){
                        inter = tmp;
                        closestObj = obj;
                    }
                }
            }
            
            //Calculate shading
            if(inter.intersect()){
                Vector n = closestObj->getNormal(inter.getP1());
                inter.setNormal(n);
                Material m = closestObj->getMaterial();
                
                //Ambient light
//                px.r += m.getDiffuse()[0] * aLight.getRgb()[0];
//                px.g += m.getDiffuse()[1] * aLight.getRgb()[1];
//                px.b += m.getDiffuse()[2] * aLight.getRgb()[2];
                
                for(auto l : pLights){
                    vector<double> rgb = calcShading(inter, l->getPos(), l->getRgb(),
                                                     closestObj->getMaterial());
                    px.r += rgb[0];
                    px.g += rgb[1];
                    px.b += rgb[2];
                }
            }
//            cout << px.r << " " << px.g << " " << px.b << endl;
        }
    }
    cout << "finished rendering." << endl;
}

//Calculate shading
vector<double> Camera::calcShading(const Intersection &inter, const Point &lPos,
                                   const vector<double> &lRgb, const Material &m){
    vector<double> rgb = {0.0, 0.0, 0.0};
    
    //Calculate vectors
    Vector v(inter.getP1(), _eye);
    v.normalize();
    Vector n = inter.getNormal();
    Vector l = Vector(inter.getP1(), lPos);
    l.normalize();
    Vector h = v + l;
    h.normalize();
    
    //Blinn-Phong shading
    double cosnl = max(0.0, n.dot(l));
    double cosnh = max(0.0, n.dot(h));
    vector<double> ks = m.getSpecular();
    vector<double> kd = m.getDiffuse();
    for(int i = 0; i < 3; i++)
        rgb[i] = kd[i] * lRgb[i] * cosnl + ks[i] * lRgb[i] * pow(cosnh, m.getPhong());
    
    return rgb;
}

//Write result to output file
void Camera::writeFile(const char outfile[]){
    cout << "writing output image." << endl;
    RgbaOutputFile file (outfile, _pw, _ph, WRITE_RGBA);
    file.setFrameBuffer (&_pixels[0][0], 1, _pw);
    file.writePixels (_ph);
    cout << "done." << endl;
}
