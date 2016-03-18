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
                     vector<Surface*> &objs,
                     vector<Light*> &lits,
                     AmbientLight **aLit,
                     vector<Material*> &mats);

int main(int argc, char * argv[]) {
    clock_t start = clock();
    
//    if (argc != 5) {
//        cerr << "useage: not enough raytra arguements" << endl;
//        return -1;
//    }
//    int p_num = atoi(argv[3]);
//    int s_num = atoi(argv[4]);
    
    int p_num = 1;
    int s_num = 1;
    char scenefile[] = "/Users/vicky/Desktop/Computer Graphics/hw1.6/test/bunny.txt";
    char outfile[] = "/Users/vicky/Desktop/Computer Graphics/hw1.6/test/bunny.exr";
    
    vector<Surface*> objs;
    vector<Material*> mats;
    vector<Light*> lits;
    AmbientLight *aLit = NULL;
    Camera *myCam = NULL;
    
//    parseSceneFile(argv[1], &myCam, objs, lits, &aLit, mats);
    parseSceneFile(scenefile, &myCam, objs, lits, &aLit, mats);
    
    BVH *root = new BVH(objs, 0, (int)objs.size() - 1, 0);
    cout << "constructed BVH tree" << endl;
    
    myCam->render(root, p_num, s_num, aLit, lits);
//    myCam->writeFile(argv[2]);
    myCam->writeFile(outfile);
    
    //clean up
    delete myCam; delete aLit;
    
    for(int i = 0; i < (int)mats.size(); ++i)
        delete mats[i];
    
    for(int i = 0; i < (int)objs.size(); ++i)
        delete objs[i];
    
    for(int i = 0; i < (int)lits.size(); ++i)
        delete lits[i];
    
    delete root;
    
    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout<< duration << "s" << endl;
    return 0;
}