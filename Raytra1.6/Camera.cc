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
void Camera::render(BVH *&root, const int &p_num,
                    const int &s_num,
                    const AmbientLight * const aLit,
                    const vector<Light*> &lits){
    cout << "render image." << endl;
    srand((unsigned)time(NULL));
    
    int print = _ph * _pw / 10.0;
    
    //for each pixel generate a ray through it
    for(int y = 0; y < _ph; ++y){
        for(int x = 0; x < _pw; ++x){
            if ((y * _pw + x) % print == 0)
                cout << ".";
            
            Vector rgb(0.0, 0.0, 0.0);
            if(p_num > 1){
                //Stratified(jittered) sampling when num > 1
                for(int i = 0; i < p_num; ++i){
                    for(int j = 0; j < p_num; ++j){
                        Ray r = generateRay(x + (i + (double)rand()/RAND_MAX) / p_num,
                                            y + (j + (double)rand()/RAND_MAX) / p_num);
                        rgb += rayColor(r, root, 10, s_num, lits);
                    }
                }
                rgb /= p_num * p_num;
            }
            else{
                Ray r = generateRay(x, y);
                rgb = rayColor(r, root, 10, s_num, lits);
            }
            
//            if(rgb.getLen() < 0.001 && aLit)
//                rgb += aLit->getRgb() * 0.08;
            
            setPixel(x, y, rgb[0], rgb[1], rgb[2]);
        }
    }
    cout << endl << "finished rendering." << endl;
}

//Recursive ray tracing
//ray_type: 1 - primary ray; 2 - reflected ray; 3 - refracted ray
Vector Camera::rayColor(const Ray &r, BVH *&root, const int &recurse_limit,
                        const int &s_num, const vector<Light*> &lits){
//                        const AmbientLight * const aLit
    if(recurse_limit == 0)
        return move(Vector(0.0, 0.0, 0.0));
    
    //color accumulator
    Vector ret_rgb(0.0, 0.0, 0.0);
    Intersection it;

    if(root->intersect(r, it)){
        Material *m = it.getMaterial();
        Point pi = r.getOri() + r.getDir() * it.getT1();
        
        //Normal at intersection
        Vector n = it.getNormal();
        
        //Vector from intersection to camera
        Vector e_i = r.getDir();
        Vector i_e = e_i * (-1.0);
        
        for(int i = 0; i < (int)lits.size(); ++i){
            //bling-phong shading
            //point light
            if (lits[i]->getType() == 1){
                //Vector from intersection to light position
                Vector i_l = Vector(pi, dynamic_cast<PointLight*>(lits[i])->getPos());
                //Two sided shading
//                if (i_e.dot(n) < 0.0)
//                    n *= -1.0;

                if(!inShadow(root, pi, i_l))
                    ret_rgb += m->phongShading(i_e, n, i_l, lits[i]->getRgb());
            }
            //area light
            else if(lits[i]->getType() == 2){
                if(s_num > 1){
                    vector<Point> samples;
                    dynamic_cast<AreaLight*>(lits[i])->generateSample(s_num, samples);
                    
                    Vector tmp_rgb(0.0, 0.0, 0.0);
                    for(auto const &pl : samples){
                        Vector i_l = Vector(pi, pl);
                        if(!inShadow(root, pi, i_l))
                            tmp_rgb += m->phongShading(i_e, n, i_l, lits[i]->getRgb());
                    }
                    ret_rgb += tmp_rgb / (s_num * s_num);
                }
                else{
                    Point pl = dynamic_cast<AreaLight*>(lits[i])->getCenter();
                    Vector i_l = Vector(pi, pl);
                    if(!inShadow(root, pi, i_l))
                        ret_rgb += m->phongShading(i_e, n, i_l, lits[i]->getRgb());
                }
            }
        }
    
        //ideal specular shading
        Vector km = m->getIdealSpec();
        if(km.getLen() > 0.0){
            //reflected ray
            Vector rfl = n * (2 * n.dot(i_e)) - i_e;
            rfl.normalize();
            Ray r_ray(pi, rfl);
            
            ret_rgb += km * rayColor(r_ray, root, recurse_limit - 1, s_num, lits);
        }
    }
    return move(ret_rgb);
}

bool Camera::inShadow(BVH *&root, const Point &pi, Vector &i_l){
    //t should be less than the distance from intersection to light position
    double max_t = i_l.getLen();
    i_l.normalize();
    
    //check shadow
    Ray s_ray(pi, i_l);
    Intersection tmp;
    return root->intersect(s_ray, tmp) && tmp.getT1() < max_t;
}

//Write result to output file
void Camera::writeFile(const char outfile[]){
    cout << "writing output image." << endl;
    RgbaOutputFile file (outfile, _pw, _ph, WRITE_RGBA);
    file.setFrameBuffer (&pixels[0][0], 1, _pw);
    file.writePixels (_ph);
    cout << "done." << endl;
}
