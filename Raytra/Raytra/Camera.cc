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
    
    //for each pixel generate a ray through it
    for(int y = 0; y < _ph; ++y){
        for(int x = 0; x < _pw; ++x){
            Ray r = generateRay(x, y);
            Vector rgb(0.0, 0.0, 0.0);
            
            //if there is an ambient light
            Vector ambient(0.0, 0.0, 0.0);
            if(aLight)
                ambient = aLight->getRgb();
            
            for(auto li : lights)
                rgb += rayColor(r, 1, 0.0001, numeric_limits<double>::max(),
                                12, li, objects);
            
            //ambient shading
            if(rgb.getLen() < 0.001)
                rgb += ambient * 0.05;

            setPixel(x, y, rgb[0], rgb[1], rgb[2]);
        }
    }
    cout << "finished rendering." << endl;
}

//Recursive ray tracing
//ray_type: 1 - primary ray; 2 - shadow ray; 3 - reflected ray; 4 - refracted ray
Vector Camera::rayColor(const Ray &r, int ray_type, double min_t, double max_t,
                        int recurse_limit, const Light *thisLight,
                        const vector<Surface*> &objects){
    if(recurse_limit == 0)
        return Vector(0.0, 0.0, 0.0);
    
    //shadow ray
    if(ray_type == 2){
        Intersection it;
        for(auto obj : objects){
            if(obj->intersect(r, it)){
                if(it.getT1() > min_t && it.getT1() < max_t)
                    return Vector(0.0, 0.0, 0.0);
            }
        }
        return thisLight->getRgb();
    }
    
    //regular ray
    //find closest intersection
    Material *m = NULL;
    Intersection it;
    
    for(auto obj : objects){
        Intersection tmp;
        if(obj->intersect(r, tmp)){
            if(tmp.getT1() > min_t && tmp.getT1() < it.getT1()){
                it = tmp;
                m = obj->getMaterial();
            }
        }
    }
    
    //color accumulator
    Vector ret_rgb(0.0, 0.0, 0.0);
    
    if(it.intersect()){
        //Normal at intersection
        Vector n = it.getNormal();
        
        //Vector from intersection to camera
        Vector i_e = r.getDir();
        i_e *= -1.0;
        
        //specular and diffuse shading
        switch (thisLight->getType()){
            //Point light
            case 'p':{
                //Vector from intersection to light position
                Vector i_l = Vector(it.getP1(), thisLight->getPos());
                
                //t should be less than the distance from intersection to light position
                double max_t = i_l.getLen();
                i_l.normalize();
                
                Ray s_ray(it.getP1(), i_l);
                
                Vector l_rgb = rayColor(s_ray, 2, min_t, max_t, 1, thisLight, objects);

                //not in shadow
                if(l_rgb.getLen() > 0.0){
                    //Two sided shading
//                        if (i_e.dot(n) < 0.0)
//                            n *= -1.0;
    
                    ret_rgb += m->phongShading(i_e, n, i_l, l_rgb);
                }
            }
                break;
    
            //Direction light
//                case 'd':{
//                    if(!inShadow(inter.getP1(), thisLight->getDir(),
//                                numeric_limits<double>::max(), objects))
//                        ret_rgb += m->lambertianShading(n, thisLight->getDir(), thisLight->getRgb());
//                }
//                    break;
        }
    
        //ideal specular shading
        Vector km = m->getIdealSpec();
        if(km.getLen() > 0.0){
            
            //reflected ray
            Vector rfl = n * (2 * n.dot(i_e)) - i_e;
            rfl.normalize();
            Ray r_ray(it.getP1(), rfl);
            
//            if(m->getRefIndex() > 0.0){
//                Vector d = r.getDir(), k;
//                double kr, kg, kb, cos, det;
//                
//                double nt = m->getRefIndex();
//                Vector att = m->getAttenuate();
//
//                if(d.dot(n) < 0)
//                    kr = kg = kb = 1.0;
//                else{
//                    kr = exp(-att[0] * inter.getT1());
//                    kg = exp(-att[1] * inter.getT1());
//                    kb = exp(-att[2] * inter.getT1());
//                    n *= -1.0;
//                    nt = 1 / nt;
//                }
//                cos = -d.dot(n);
//                det = 1 - (1 - cos * cos) / (nt * nt);
//
//                //Refraction
//                if(det >= 0){
//                    k = Vector(kr, kg, kb);
//                    Vector t = (d + n * cos) / nt - n * sqrt(det);
//                    t.normalize();
//                    Ray t_ray(inter.getP1(), t);
//                    
//                    double R0 = pow((nt - 1)/(nt + 1), 2);
//                    double R_theta = R0 + (1 - R0) * pow((1 - cos), 5);
//                    double max_t = numeric_limits<double>::max();
//                    
//                    Vector color_rfl = rayColor(r_ray, 3, 0.0001, max_t, recurse_limit - 1, thisLight, objects);
//                    Vector color_rfr = rayColor(t_ray, 4, 0.0001, max_t, recurse_limit - 1, thisLight, objects);
//                    ret_rgb += k * km * (color_rfl * R_theta + color_rfr * (1 - R_theta));
//                }
//            }
//            else
                ret_rgb += km * rayColor(r_ray, 3, 0.0001, max_t, recurse_limit - 1, thisLight, objects);
        }
    }
    
    return ret_rgb;
}

//Write result to output file
void Camera::writeFile(const char outfile[]){
    cout << "writing output image." << endl;
    RgbaOutputFile file (outfile, _pw, _ph, WRITE_RGBA);
    file.setFrameBuffer (&_pixels[0][0], 1, _pw);
    file.writePixels (_ph);
    cout << "done." << endl;
}
