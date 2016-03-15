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
    
    if (argc != 5) {
        cerr << "useage: not enough raytra arguements" << endl;
        return -1;
    }
    int p_num = atoi(argv[3]);
    int s_num = atoi(argv[4]);
    
//    int p_num = 2;
//    int s_num = 3;
//    char scenefile[] = "/Users/vicky/Desktop/Computer Graphics/hw1.6/test/colorspheres.txt";
//    char outfile[] = "/Users/vicky/Desktop/Computer Graphics/hw1.6/test/colorspheres.exr";
    
    vector<Surface*> objects;
    vector<Material*> materials;
    vector<Light*> lights;
    AmbientLight *aLight = NULL;
    Camera *myCam = NULL;
    
    parseSceneFile(argv[1], &myCam, objects, lights, &aLight, materials);
//    parseSceneFile(scenefile, &myCam, objects, lights, &aLight, materials);
    
    BVH *root = new BVH(objects, 0, (int)objects.size() - 1, 0);
    cout << "constructed BVH tree" << endl;
    
    myCam->render(root, p_num, s_num, aLight, lights);
    myCam->writeFile(argv[2]);
//    myCam->writeFile(outfile);
    
    //manually clear memory
    delete myCam; delete aLight;
    deleteTree(root);
    
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