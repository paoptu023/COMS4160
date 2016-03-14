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
    pixels.resizeErase(0, 0);
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
    pixels.resizeErase(ph, pw);
}

//Set up the camera coordinates
void Camera::setUvw(const Vector &d){
    _w = d * (-1.0);
    _w.normalize();
    if(1 - abs(_w[1]) < 0.0001){
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
    return move(Ray(_eye, dir));
}

//Render the image
void Camera::render(BVH *&root, int p_num, int s_num,
//                    const AmbientLight * const aLight,
                    const vector<Light*> &lights){
    cout << "render image." << endl;
    
    //for each pixel generate a ray through it
    for(int y = 0; y < _ph; ++y){
        for(int x = 0; x < _pw; ++x){
            Ray r = generateRay(x, y);
            
            Vector rgb = rayColor(r, root, 10, lights, p_num, s_num);
            
            setPixel(x, y, rgb[0], rgb[1], rgb[2]);
        }
    }
    cout << "finished rendering." << endl;
}

//Recursive ray tracing
//ray_type: 1 - primary ray; 2 - reflected ray; 3 - refracted ray
Vector Camera::rayColor(const Ray &r, BVH * &root,
                        int recurse_limit,
                        const vector<Light*> &lights,
//                        const AmbientLight * const aLight,
                        int p_num, int s_num){
    if(recurse_limit == 0)
        return move(Vector(0.0, 0.0, 0.0));
    
    //color accumulator
    Vector ret_rgb(0.0, 0.0, 0.0);
    Material *m = NULL;
    Intersection it;
    
    if(root->intersect(r, it))
        m = it.getMaterial();
    
    if(m != NULL){
        Point p1 = it.getP1();
        
        //Normal at intersection
        Vector n = it.getNormal();
        
        //Vector from intersection to camera
        Vector e_i = r.getDir();
        Vector i_e = e_i * (-1.0);
        
        for(auto li : lights){
            //bling-phong shading
            if (li->getType() == 'p'){
                //Vector from intersection to light position
                Vector i_l = Vector(p1, li->getPos());
                
                //t should be less than the distance from intersection to light position
                double max_t = i_l.getLen();
                i_l.normalize();
                
                //check shadow
                Ray s_ray(p1, i_l);
                bool inShadow = false;
                
                Intersection tmp;
                if(root->intersect(s_ray, tmp) && tmp.getT1() < max_t){
                    inShadow = true;
                }

                //Two sided shading
//                if (i_e.dot(n) < 0.0)
//                    n *= -1.0;
                
                //not in shadow
                if(!inShadow)
                    ret_rgb += m->phongShading(i_e, n, i_l, li->getRgb());
            }
        }
        
        //add ambient if needed
//        if(ret_rgb.getLen() < 0.001 && aLight && ray_type == 1)
//            ret_rgb += aLight->getRgb() * 0.05;
    
        //ideal specular shading
        Vector km = m->getIdealSpec();
        if(km.getLen() > 0.0){
            //reflected ray
            Vector rfl = n * (2 * n.dot(i_e)) - i_e;
            rfl.normalize();
            Ray r_ray(p1, rfl);
            
            ret_rgb += km * rayColor(r_ray, root, recurse_limit - 1, lights, p_num, s_num);
        }
    }
    return move(ret_rgb);
}

//Write result to output file
void Camera::writeFile(const char outfile[]){
    cout << "writing output image." << endl;
    RgbaOutputFile file (outfile, _pw, _ph, WRITE_RGBA);
    file.setFrameBuffer (&pixels[0][0], 1, _pw);
    file.writePixels (_ph);
    cout << "done." << endl;
}
