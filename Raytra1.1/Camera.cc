//
//  Camera.cpp
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Qi Wang. All rights reserved.
//

#include "Camera.h"
extern Array2D<Rgba> pixels;
extern vector<Surface*> objects;

//Default constructor
Camera::Camera(){
    eye = Point(0.0, 0.0, 0.0);
    f = 0.0;
    iw = ih = 0.0;
    nw = nh = 0.0;
    u = v = w = Vector(0.0, 0.0, 0.0);
}

//Constructor
Camera::Camera(const Point &p, const Vector &dir, double d, double width, double height, int pw, int ph){
    eye = p;
    f = d;
    iw = width;
    ih = height;
    nw = pw;
    nh = ph;
    setUvw(dir);
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
    
    u = d.cross(up);
    v = u.cross(d);
    w = d * (-1.0);
    u.normalize();
    v.normalize();
    w.normalize();
}

//Generate ray through the current pixel
Ray Camera::generateRay(double i, double j){
    //Convert pixel coordinates to image plane coordinates
    double l = -iw/2.0;
    double t = ih/2.0;
    double U = l + iw * (i + 0.5) / nw;
    double V = t - ih * (j + 0.5) / nh;
    
    
    Vector dir = w * (-f)+ u * U + v * V;
    dir.normalize();
    Ray r(eye, dir);
    return r;
}

//Render the image
void Camera::render(vector<Surface*> objs){
    cout << "render image." << endl;
    pixels.resizeErase(nh, nw);
    for(int y = 0; y < nh; y++){
        for(int x = 0; x < nw; x++){
            Ray r = generateRay(x, y);
            for(int k = 0; k < objects.size(); k++){
                double t1, t2;
                Rgba & px = pixels[y][x]; //gets current pixel
                px.a = 1;
                px.g = 0;
                px.b = 0;
                //If intersects, set color to red
                if(objects[k]->intersect(r, t1, t2)){
                    px.r = 1;
                    break;
                }
                else
                    px.r = 0;
            }
        }
    }
    cout << "finished rendering." << endl;
}


void writeRgba (const char fileName[],
                const Rgba *pixels,
                int width,
                int height)
{
    RgbaOutputFile file (fileName, width, height, WRITE_RGBA);
    file.setFrameBuffer (pixels, 1, width);
    file.writePixels (height);
}

//Write result to output file
void Camera::writeFile(const char outfile[]){
    cout << "writing output image." << endl;
    writeRgba (outfile, &pixels[0][0], nw, nh);
    cout << "done." << endl;
}
