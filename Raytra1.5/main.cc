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
                     vector<Light*> &lights, AmbientLight **aLight, vector<Material*> &materials);

int main(int argc, char * argv[]) {
    clock_t start = clock();
    
//    if (argc < 3) {
//        cerr << "useage: raytra scenefilename" << endl;
//        return -1;
//    }
//    char *scenefile = argv[1];
//    char *outfile = argv[2];
//    
//    bool withBbox = true;
//    bool bboxOnly = false;
//    bool withBVH = false;
//    
//    if(argc == 4){
//        int k = atoi(argv[3]);
//        switch(k){
//            case 0:
//                withBbox = false;
//                break;
//            case 1:
//                bboxOnly = true;
//                break;
//            case 2:{
//                withBVH = true;
//                bboxOnly = true;
//            }
//                break;
//            case 3:
//                withBVH = true;
//                break;
//        }
//    }
    
    bool bboxOnly = false;
    bool withBVH = true;
    
    if(bboxOnly)    cout << "only render bounding boxes" << endl;
    
    if(withBVH)
        cout << "BVH mode" << endl;
    else
        cout << "just bounding box mode" << endl;
    
    char scenefile[] = "/Users/vicky/Desktop/Computer Graphics/hw1.5/test/teapot.txt";
    char outfile[] = "/Users/vicky/Desktop/Computer Graphics/hw1.5/test/teapot.exr";
    
    vector<Surface*> objects;
    vector<Material*> materials;
    vector<Light*> lights;
    AmbientLight *aLight = NULL;
    Camera *myCam = NULL;
    BVH *root = NULL;
    
    parseSceneFile(scenefile, &myCam, objects, lights, &aLight, materials);
    
    if(withBVH)
        root = new BVH(objects, 0, (int)objects.size() - 1, 0);
    
    myCam->render(objects, lights, aLight, root, bboxOnly);
    myCam->writeFile(outfile);
    
    delete myCam; delete aLight;
//    if(root)
//        delete root;
    
    for(auto m : materials)
        delete m;
    materials.clear();
    
    for(auto obj : objects)
        delete obj;
    objects.clear();
    
    for(auto li : lights)
        delete li;
    lights.clear();
    
    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout<< duration << "s" << endl;
    return 0;
}
