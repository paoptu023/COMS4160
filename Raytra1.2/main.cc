//
//  main.cc
//  Raytra
//
//  Created by Qi Wang on 2/5/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "PointLight.h"
#include "AmbientLight.h"
#include "Surface.h"
#include "Camera.h"

void parseSceneFile (char *filnam, Camera &myCam, vector<Surface*> &objects,
                     AmbientLight &aLight, vector<PointLight*> &pLights);

int main(int argc, char * argv[]) {
    if (argc != 3) {
        cerr << "useage: raytra scenefilename" << endl;
        return -1;
    }
    char *scenefile = argv[1];
    char *outfile = argv[2];
    
    vector<Surface*> objects;
    Camera myCam;
    AmbientLight aLight;
    vector<PointLight*> pLights;
    
//    char scenefile[] = "/Users/vicky/Desktop/Computer Graphics/test/scene2.txt";
//    char outfile[] = "/Users/vicky/Desktop/Computer Graphics/test/hw1.2.exr";
    parseSceneFile(scenefile, myCam, objects, aLight, pLights);
    myCam.render(objects, aLight, pLights);
    myCam.writeFile(outfile);
    return 0;
}
