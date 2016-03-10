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

void parseSceneFile (char *filnam, Camera **myCam,
                     vector<Surface*> &objects,
                     vector<Light*> &lights,
                     AmbientLight **aLight,
                     vector<Material*> &materials);

void deleteTree(BVH *root){
    if(root){
        deleteTree(dynamic_cast<BVH*>(root->left));
        deleteTree(dynamic_cast<BVH*>(root->right));
        delete root;
    }
}

int main(int argc, char * argv[]) {
    clock_t start = clock();
    
    if (argc < 3) {
        cerr << "useage: raytra scenefilename" << endl;
        return -1;
    }
    char *scenefile = argv[1];
    char *outfile = argv[2];

    bool bboxOnly = false;
    bool withBVH = true;

    if(argc == 4){
        int k = atoi(argv[3]);
        switch(k){
            case 0:
                withBVH = false;
                break;
            case 1:{
                bboxOnly = true;
                withBVH = false;
            }
                break;
            case 2:
                bboxOnly = true;
                break;
        }
    }
    
    if(bboxOnly)
        cout << "only render bounding boxes" << endl;
    
    if(withBVH)
        cout << "BVH mode." << endl;
    else
        cout << "just bounding box mode." << endl;
    
//    char scenefile[] = "/Users/vicky/Desktop/Computer Graphics/hw1.5/test/colorspheres.txt";
//    char outfile[] = "/Users/vicky/Desktop/Computer Graphics/hw1.5/test/colorspheres_box.exr";
    
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
    
    //manually clear memory
    delete myCam; delete aLight; deleteTree(root);
    
    for(auto m : materials)
        delete m;
    
    for(auto obj : objects)
        delete obj;
    
    for(auto li : lights)
        delete li;
    
    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout<< duration << "s" << endl;
    return 0;
}