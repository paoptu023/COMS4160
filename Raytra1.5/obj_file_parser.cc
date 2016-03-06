#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

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
//
// If you are using the supplied Parser class, you should probably make this
// a method on it: Parser::read_wavefront_file().
//
void read_wavefront_file (
    const char *file,
    vector<int> &tris,
    vector<float> &verts)
{
    
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



// Example usage.
//
// In your code, you are more likely to call read_wavefront_file() from within the P.parse() routine
// (when a "w" is encountered in the input file), at
// which point you will create (with "new") the new triangles and push them onto the surface list.
//
//int main (int argc, const char * argv[])
//{
//
//    
//    Parser P;
//    
//    std::vector<int> tris;
//    std::vector <float> verts;
//    
//    P.read_wavefront_file (argv[1], tris, verts);
//    
//    // At this point, tris is a list of triangle vertex indices, and
//    // verist is a list of vertex coordinates (x, y, z for each vertex)
//  
//    
//    return 0;
//}
