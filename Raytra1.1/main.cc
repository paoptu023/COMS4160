//
//  main.cpp
//  Raytra
//
//  Created by Qi Wang on 2/5/16.
//  Copyright © 2016 Qi Wang. All rights reserved.
//
#include "Raytra.h"
#include "Surface.h"
#include "Camera.h"

vector<Surface*> objects;
Array2D<Rgba> pixels;
Camera *myCam;
void parseSceneFile (char *filnam);

int main(int argc, char * argv[]) {
    if (argc != 2) {
        cerr << "useage: raytra scenefilename" << endl;
        return -1;
    }
    char *scenefile = argv[1];
    char *outfile = "hw1.1.exr";
    
//    char scenefile[] = "/Users/vicky/Desktop/Computer Graphics/hw1.1/scene2.txt";
//    char outfile[] = "/Users/vicky/Desktop/Computer Graphics/hw1.1/hw1.exr";
    parseSceneFile(scenefile);
    myCam->render(objects);
    myCam->writeFile(outfile);
    return 0;
}
