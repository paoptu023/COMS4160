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
    if (argc != 3) {
        cerr << "useage: raytra scenefilename" << endl;
        return -1;
    }
    char *scenefile = argv[1];
    char *outfile = argv[2];
    
    vector<Surface*> objects;
    Camera *myCam;
    vector<Material*> materials;
    AmbientLight *aLight = NULL;
    vector<Light*> lights;
    
//    char scenefile[] = "/Users/vicky/Desktop/Computer Graphics/hw1.3/test/scene1.txt";
//    char outfile[] = "/Users/vicky/Desktop/Computer Graphics/hw1.3/test/hw1.3_11.exr";
    
    parseSceneFile(scenefile, &myCam, objects,
                   lights, &aLight, materials);
    
    myCam->render(objects, lights, aLight);
    myCam->writeFile(outfile);
    
    delete myCam;
    delete aLight;
    return 0;
}
