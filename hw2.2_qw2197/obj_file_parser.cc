#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "amath.h"

typedef amath::vec4  point4;

void read_wavefront_file (const char *file, std::vector<point4> &vertices,
                          std::vector<vec4> &norms){
    std::ifstream in(file);
    char buffer[1025];
    std::string cmd;
    std::vector<float> verts;
    std::vector<int> tris;
    
    tris.clear();
    for (int line=1; in.good(); line++) {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
                
        cmd="";
        
        std::istringstream iss (buffer);
        
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
            // indices start with 0, so we're shifting everything down by 1
            tris.push_back (i-1);
            tris.push_back (j-1);
            tris.push_back (k-1);
        } 
        else {
            std::cerr << "Parser error: invalid command at line " << line << std::endl;
        }
        
     }
    
    in.close();
    
    std::cout << "found this many tris, verts: " << tris.size () / 3.0 << "  "
    << verts.size () / 3 << std::endl;
    
    std::vector<vec4> verts_norms = std::vector<vec4>(verts.size() / 3, vec4(0.0, 0.0, 0.0, 0.0));
    float x1, y1, z1, x2, y2, z2, x3, y3, z3;
    for(int i = 0; i < (int)tris.size(); i += 3){
        x1 = verts[3 * tris[i]];
        y1 = verts[3 * tris[i] + 1];
        z1 = verts[3 * tris[i] + 2];
        
        x2 = verts[3 * tris[i + 1]];
        y2 = verts[3 * tris[i + 1] + 1];
        z2 = verts[3 * tris[i + 1] + 2];
        
        x3 = verts[3 * tris[i + 2]];
        y3 = verts[3 * tris[i + 2] + 1];
        z3 = verts[3 * tris[i + 2] + 2];
        
        vertices.push_back(point4(x1, y1, z1, 1.0));
        vertices.push_back(point4(x2, y2, z2, 1.0));
        vertices.push_back(point4(x3, y3, z3, 1.0));
        
        vec4 norm = normalize(vec4(cross(vertices[i + 1] - vertices[i],
                                         vertices[i + 2] - vertices[i + 1]), 0.0));
        verts_norms[tris[i]] += norm;
        verts_norms[tris[i + 1]] += norm;
        verts_norms[tris[i + 2]] += norm;
    }
    
    for(int i = 0; i < (int)verts_norms.size(); ++i)
        verts_norms[i] = normalize(verts_norms[i]);
    
    norms = std::vector<vec4>(vertices.size(), vec4(0.0, 0.0, 0.0, 0.0));
    for (int i = 0; i < (int)tris.size(); i += 3){
        norms[i] = verts_norms[tris[i]];
        norms[i + 1] = verts_norms[tris[i + 1]];
        norms[i + 2] = verts_norms[tris[i + 2]];
    }
}
