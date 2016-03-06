#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Light.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Camera.h"

#define IM_DEBUGGING

// Given the name of a wavefront (OBJ) file that consists JUST of
// vertices, triangles, and comments, read it into the tris and verts
// vectors.
//
// tris is a vector of ints that is 3*n long, where n is the number of
// triangles. The ith triangle has vertex indexes 3*i, 3*i+1, and 3*i+2.
//
// The ith triangle has vertices:
//
//     verts[3*tris[3*i]], verts[3*tris[3*i]+1], verts[3*tris[3*i]+2],
//     verts[3*tris[3*i+1]], verts[3*tris[3*i+1]+1], verts[3*tris[3*i+1]+2],
//     verts[3*tris[3*i+2]], verts[3*tris[3*i+2]+1], verts[3*tris[3*i+2]+2]
//
// given in counterclockwise order with respect to the surface normal
void read_wavefront_file (const char *file,
                          vector<int> &tris,
                          vector<float> &verts){
    // clear out the tris and verts vectors:
    tris.clear ();
    verts.clear ();
    
    ifstream in(file);
    char buffer[1025];
    string cmd;
    
    
    for (int line=1; in.good(); line++) {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
        
        cmd="";
        
        istringstream iss (buffer);
        
        iss >> cmd;
        
        if (cmd[0]=='#' || cmd[0] == 'g' || cmd.empty()) {
            // ignore comments or blank lines
            continue;
        }
        else if (cmd=="v") {
            // got a vertex:
            
            // read in the parameters:
            double pa, pb, pc;
            iss >> pa >> pb >> pc;
            
            verts.push_back (pa);
            verts.push_back (pb);
            verts.push_back (pc);
        }
        else if (cmd=="f") {
            // got a face (triangle)
            
            // read in the parameters:
            int i, j, k;
            iss >> i >> j >> k;
            
            // vertex numbers in OBJ files start with 1, but in C++ array
            // indices start with 0, so we're shifting everything down by
            // 1
            tris.push_back (i-1);
            tris.push_back (j-1);
            tris.push_back (k-1);
        }
        else {
            cerr << "Parser error: invalid command at line " << line << endl;
        }
        
    }
    
    in.close();
    
    cout << "found this many tris, verts: " << tris.size () / 3.0 << "  " << verts.size () / 3.0 << endl;
}

// this is called from the parseSceneFile function, which uses
// it to get the float from the correspoding position on the line.
//
// return the corresponding token in the inString. Errors out
// if you've asked for more than are in the line.
//
// you really don't need to know what is going on in here, I think.
//
double getTokenAsFloat (string inString, int whichToken)
{
    
    double thisFloatVal = 0.;    // the return value
    
     if (whichToken == 0) {
         cerr << "error: the first token on a line is a character!" << endl;
         exit (-1);
     }
    
    // c++ string class has no super-easy way to tokenize, let's use c's:
    char *cstr = new char [inString.size () + 1];
    
    strcpy (cstr, inString.c_str());
    
    char *p = strtok (cstr, " ");
    if (p == 0) {
        cerr << "error: the line has nothing on it!" << endl;
        exit (-1);
    }
    
    for (int i = 0; i < whichToken; i++) {
        p = strtok (0, " ");
        if (p == 0) {
//            cerr << "error: the line is not long enough for your token request!" << endl;
//            exit (-1);
            return numeric_limits<double>::min();
        }
    }
    
    thisFloatVal = atof (p);
    
    delete[] cstr;
    
    return thisFloatVal;
}


//
// read the scene file.
//
// You'll need a few globals (or add arguments to this function): for the
// list of surfaces (geometric objects like spheres, triangles, planes) and
// another for the lights. These can be of type std::vector. You'll also
// need a global (or other parameter) for the camera.
//
// This should be pretty self-explanatory: it reads through the lines, and
// using the first character figures out what kind of command it is. It
// then calls the "getTokenAsFloat" routine to pull out the needed values.
// NOTE: since different commands take different number of arguments, you
// must take care not to call getTokenAsFloat for an index that is beyond the
// end of the line!
//
// One tricky bit: when a material is read in, we want
// to keep a pointer to it so that for the next geometric object read in ,
// we can add that material to the object. In the code that follows, I use the
// variable "lastSurfaceLoaded" to do that, but the code is commented out since
// I don't know the class names you will be using.
//
// Very minimal error check here. You might improve it slightly, but we'll
// only use "correct" scene files.
//
//
void parseSceneFile (char *filnam, Camera **myCam, vector<Surface*> &objects,
                     vector<Light*> &lights, AmbientLight **aLight, vector<Material*> &materials)
{
    
    ifstream inFile(filnam);    // open the file
    string line;
    
    if (! inFile.is_open ()) {  // if it's not open, error out.
        cerr << "can't open scene file" << endl;
        exit (-1);
    }
    
    
    // Note: you'll have to keep track of whatever the last material
    // you loaded in was, so you can apply it to any geometry that gets loaded. 
    // So here, you'll have something like:
    //
    // myMaterialClass *lastMaterialLoaded = 0;  // 0 or maybe a default material?
    //
    // and each time you load in a new piece of geometry (sphere, triangle, plane)
    // you will set its material to lastMaterialLoaded.
    
    while (! inFile.eof ()) {   // go through every line in the file until finished
        
        getline (inFile, line); // get the line
        
        switch (line[0])  {     // we'll decide which command based on the first character
            
            //
            // geometry types:
            //
            // NOTE: whichever type of geo you load in, set its material to
            // be "lastMaterialLoaded"
            //
            case 's':{ //sphere
                double x, y, z, r;
                x = getTokenAsFloat (line, 1); 
                y = getTokenAsFloat (line, 2); 
                z = getTokenAsFloat (line, 3); 
                r = getTokenAsFloat (line, 4); 
                
                Sphere *mySphere = new Sphere(materials.back(), Point(x, y, z), r);
                objects.push_back(mySphere);
                // build your sphere here from the parameters
                // i.e. you must call your sphere constructor and set its position
                // and radius from the above values. You must also put your new
                // sphere into the objects list (which can be global)
                // So something like;
                // mySphereClass *ms = new mySphereClass (x, y, z, r);   // make a new instance of your sphere class
                // ms->setMaterial (lastMaterialLoaded)
                // objectsList->push_back (ms);  // objectsList is a global std:vector<surface *> for example.
                
#ifdef IM_DEBUGGING
                // if we're debugging, show what we got:
//                cout << "got a sphere with ";
//                cout << "parameters: " << x << " " << y << " " << z << " " << r << endl;
            }
#endif
                break;
            
            case 't':{ // triangle
                double x1, y1, z1, x2, y2, z2, x3, y3, z3;
                x1 = getTokenAsFloat (line, 1);
                y1 = getTokenAsFloat (line, 2);
                z1 = getTokenAsFloat (line, 3);
                x2 = getTokenAsFloat (line, 4);
                y2 = getTokenAsFloat (line, 5);
                z2 = getTokenAsFloat (line, 6);
                x3 = getTokenAsFloat (line, 7);
                y3 = getTokenAsFloat (line, 8);
                z3 = getTokenAsFloat (line, 9);
                
                Triangle *myTri = new Triangle(x1, y1, z1, x2, y2, z2, x3, y3, z3, materials.back());
                objects.push_back(myTri);
//                cout << "got a triangle with ";
//                cout << "parameters: " << x1 << " " << y1 << " " << z1 << " " <<
//                        x2 << " " << y2 << " " << z2 << " " <<
//                        x3 << " " << y3 << " " << z3 << endl;
            }
                break;
                
            case 'p':{ // plane
                double nx, ny, nz, d;
                nx = getTokenAsFloat (line, 1);
                ny = getTokenAsFloat (line, 2);
                nz = getTokenAsFloat (line, 3);
                d = getTokenAsFloat (line, 4);
                Plane *myPlane = new Plane(nx, ny, nz, d, materials.back());
                objects.push_back(myPlane);
//                cout << "got a plane with ";
//                cout << "parameters: " << nx << " " << ny << " " << nz << " " << d << endl;
            }
                break;
                
            //
            // camera:
            //
            case 'c':{
                // one trick here: the cameras pixel count (width, height) are integers,
                // so cast them.
                double x, y, z, vx, vy, vz, d, iw, ih;
                int pw, ph;
                x = getTokenAsFloat (line, 1);
                y = getTokenAsFloat (line, 2);
                z = getTokenAsFloat (line, 3);
                vx = getTokenAsFloat (line, 4);
                vy = getTokenAsFloat (line, 5);
                vz = getTokenAsFloat (line, 6);
                d = getTokenAsFloat (line, 7);
                iw = getTokenAsFloat (line, 8);
                ih = getTokenAsFloat (line, 9);
                pw = (int) getTokenAsFloat (line, 10);
                ph = (int) getTokenAsFloat (line, 11);
                
                *myCam = new Camera(Point(x, y, z), Vector(vx, vy, vz), d, iw, ih, pw, ph);
//                cout << "got a camera with ";
//                cout << "parameters: " << x << " " << y << " " << z << " " <<
//                    vx << " " << vy << " " << vz << " " << d << " " <<
//                    iw << " " << ih << " " << pw << " " << ph << endl;
            }
                break;
        
            //
            // lights:
            //
            case 'l':   // light
                
                // slightly different from the rest, we need to examine the second param,
                // which is at the third position on the line:
                switch (line[2]) {
                    case 'p':{   // point light
                        double x, y, z, r, g, b;
                        x = getTokenAsFloat (line, 2);
                        y = getTokenAsFloat (line, 3);
                        z = getTokenAsFloat (line, 4);
                        r = getTokenAsFloat (line, 5);
                        g = getTokenAsFloat (line, 6);
                        b = getTokenAsFloat (line, 7);
                        
                        PointLight *pl = new PointLight(Point(x, y, z), r, g, b);
                        lights.push_back(pl);
//                        cout << "got a point light with ";
//                        cout << "parameters: " << x << " " << y << " " << z << " " << r <<
//                        " " << g << " " << b << " " << endl;
                    }
                        break;
                        
                    case 'd':{   // directional light
                        double x, y, z, r, g, b;
                        x = getTokenAsFloat (line, 2);
                        y = getTokenAsFloat (line, 3);
                        z = getTokenAsFloat (line, 4);
                        r = getTokenAsFloat (line, 5);
                        g = getTokenAsFloat (line, 6);
                        b = getTokenAsFloat (line, 7);
                        
                        DirectionLight *dl = new DirectionLight(x, y, z, r, g, b);
                        lights.push_back(dl);
                    }
                        break;
                        
                    case 'a':{   // ambient light
                        double r, g, b;
                        r = getTokenAsFloat (line, 2);
                        g = getTokenAsFloat (line, 3);
                        b = getTokenAsFloat (line, 4);
                        *aLight = new AmbientLight(r, g, b);
                    }
                        break;
                        
                }
                break;
            
            //
            // materials:
            //
            case 'm':{
                // the trick here: we should keep a pointer to the last material we read in,
                // so we can apply it to any subsequent geometry. Say it's called "lastMaterialLoaded"
                // we migh then do something like this:
                //
                //  1. read in the 10 material parameters: dr, dg, db, sr, sg, sb, r, ir, ig, ib
                //  2. call lastMaterialLoaded->setMaterial(dr, dg, db,...);
                //
                double dr, dg, db, sr, sg, sb, r, ir, ig, ib;
                dr = getTokenAsFloat (line, 1);
                dg = getTokenAsFloat (line, 2);
                db = getTokenAsFloat (line, 3);
                sr = getTokenAsFloat (line, 4);
                sg = getTokenAsFloat (line, 5);
                sb = getTokenAsFloat (line, 6);
                r = getTokenAsFloat (line, 7);
                ir = getTokenAsFloat (line, 8);
                ig = getTokenAsFloat (line, 9);
                ib = getTokenAsFloat (line, 10);
                
                Material *m = new Material(dr, dg, db, sr, sg, sb, r, ir, ig, ib);
                
                double ni = -1.0, ar = -1.0, ag = -1.0, ab = -1.0;
                ni = getTokenAsFloat (line, 11);
                ar = getTokenAsFloat (line, 12);
                ag = getTokenAsFloat (line, 13);
                ab = getTokenAsFloat (line, 14);
                if(ni > numeric_limits<double>::min())
                    m->setRefraction(ni, ar, ag, ab);
                
                materials.push_back(m);
//                cout << "got a material with ";
//                cout << "parameters: " << dr << " " << dg << " " << db << " "
//                        << sr << " " << sg << " " << sb << " " << r << " "
//                        << ir << " " << ig << " " << ib << endl;
            }
                break;
            
            //
            // wavefront obj file:
            //
            case 'w':{
                string objFile = line.substr(2, line.size() - 2);
                vector<int> tris;
                vector<float> verts;
                read_wavefront_file (&objFile[0], tris, verts);
                
                double x1, y1, z1, x2, y2, z2, x3, y3, z3;
                for(int i = 0; i < (int)tris.size() / 3; ++i){
                    //verts[3*tris[3*i]], verts[3*tris[3*i]+1], verts[3*tris[3*i]+2],
                    //verts[3*tris[3*i+1]], verts[3*tris[3*i+1]+1], verts[3*tris[3*i+1]+2],
                    //verts[3*tris[3*i+2]], verts[3*tris[3*i+2]+1], verts[3*tris[3*i+2]+2]
                    x1 = verts[3 * tris[3 * i]];
                    y1 = verts[3 * tris[3 * i] + 1];
                    z1 = verts[3 * tris[3 * i] + 2];
                    
                    x2 = verts[3 * tris[3 * i + 1]];
                    y2 = verts[3 * tris[3 * i + 1] + 1];
                    z2 = verts[3 * tris[3 * i + 1] + 2];
                    
                    x3 = verts[3 * tris[3 * i + 2]];
                    y3 = verts[3 * tris[3 * i + 2] + 1];
                    z3 = verts[3 * tris[3 * i + 2] + 2];
                    
                    Triangle *myTri = new Triangle(x1, y1, z1, x2, y2, z2, x3, y3, z3, materials.back());
                    objects.push_back(myTri);
                }
            }
                break;
                
            case '/':
                // don't do anything, it's a comment
                break;

            //
            // options
            //
            case 'o':   // make your own options if you wish
                break;
        }
        
    }
}
