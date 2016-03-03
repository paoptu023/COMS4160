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
#include "Light.h"
#include "Surface.h"
#include "Camera.h"

void parseSceneFile (char *filnam, Camera **myCam, vector<Surface*> &objects,
                     vector<Light*> &lights, AmbientLight **aLight,
                     vector<Material*> &materials);

int main(int argc, char * argv[]) {
//    if (argc != 3) {
//        cerr << "useage: raytra scenefilename" << endl;
//        return -1;
//    }
//    char *scenefile = argv[1];
//    char *outfile = argv[2];
    
    clock_t start = clock();
    
    char scenefile[] = "/Users/vicky/Desktop/Computer Graphics/hw1.4/test/teapot.txt";
    char outfile[] = "/Users/vicky/Desktop/Computer Graphics/hw1.4/test/teapot.exr";
    
    vector<Surface*> objects;
    Camera *myCam = NULL;
    vector<Material*> materials;
    AmbientLight *aLight = NULL;
    vector<Light*> lights;
    
    parseSceneFile(scenefile, &myCam, objects, lights, &aLight, materials);
    
    myCam->render(objects, lights, aLight);
    myCam->writeFile(outfile);
    
    delete myCam; delete aLight;
    
    for(auto obj : objects)
        delete obj;
    objects.clear();
    
    for(auto m : materials)
        delete m;
    materials.clear();
    
    for(auto li : lights)
        delete li;
    lights.clear();
    
    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout<< duration << "s" << endl;
    return 0;
}
