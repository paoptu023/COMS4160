#include "parser.h"

bool is_wavefront_file(const char *file) {
    ifstream in(file);
    char buffer[1025];
    string cmd;
    vector<float> verts;
    vector<int> tris;
    
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
        else if (cmd=="v")
            return true;
        else
            return false;
    }
    return false;
}

void read_wavefront_file (const char *file,
                          vector<point4> &vertices,
                          vector<vec4> &norms) {
    ifstream in(file);
    char buffer[1025];
    string cmd;
    vector<float> verts;
    vector<int> tris;
    
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
            // indices start with 0, so we're shifting everything down by 1
            tris.push_back (i-1);
            tris.push_back (j-1);
            tris.push_back (k-1);
        } 
        else {
            cerr << "Parser error: invalid command at line " << line << endl;
        }
        
     }
    
    in.close();
    
    cout << "found this many tris, verts: " << tris.size () / 3.0 << "  "
    << verts.size () / 3 << endl;
    
    vector<vec4> verts_norms = vector<vec4>(verts.size() / 3, vec4(0.0, 0.0, 0.0, 0.0));
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
    
    norms = vector<vec4>(vertices.size(), vec4(0.0, 0.0, 0.0, 0.0));
    for (int i = 0; i < (int)tris.size(); i += 3){
        norms[i] = verts_norms[tris[i]];
        norms[i + 1] = verts_norms[tris[i + 1]];
        norms[i + 2] = verts_norms[tris[i + 2]];
    }
}

void read_bezier_file (const char *file,
                       vector<Bezier> &surfaces) {
    ifstream in(file);
    char buffer[1025];
    
    int surf_num;
    in.getline(buffer,1024);
    buffer[in.gcount()]=0;
    istringstream iss (buffer);
    iss >> surf_num;
    
    vector<point4> points;
    for (int i = 0; i < surf_num; ++i){
        int u_deg, v_deg;
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
        iss.clear();
        iss.str(buffer);
        iss >> u_deg >> v_deg;
    
        points.clear();
        float x, y, z;
        for (int j = 0; j <= v_deg; ++j) {
            in.getline(buffer,1024);
            buffer[in.gcount()]=0;
            iss.clear();
            iss.str(buffer);
            for (int k = 0; k <= u_deg; ++k) {
                iss >> x >> y >> z;
                points.push_back(point4(x, y, z, 1.0));
            }
        }
        surfaces.push_back(Bezier(points, u_deg, v_deg));
    }
    in.close();
}

void makeTris (vector<Bezier> &surfaces, vector<point4> &vertices,
               vector<vec4> &norms, const int sample_level) {
    vector<point4> uv_verts;
    vector<vec4> uv_norms;
    for (int i = 0; i < (int) surfaces.size(); ++i)
        surfaces[i].sample(sample_level, uv_verts, uv_norms);
    
    vertices.clear();
    norms.clear();
    // Triangulate
    int disp = 0;
    for (int i = 0; i < (int) surfaces.size(); ++i) {
        int samples_u = surfaces[i].getUdegree() * sample_level;
        int samples_v = surfaces[i].getVdegree() * sample_level;
        
        int jump = samples_u * samples_v;
        for (int v = 0; v < samples_v - 1; ++v){
            for (int u = 0; u < samples_u - 1; ++u) {
                // triange 1
                // 6 * k, 6 * k + 1, 6 * k + 2
                int p1 = disp + v * samples_u + u;
                vertices.push_back(uv_verts[p1]);
                norms.push_back(uv_norms[p1]);
                
                int p2 = disp + v * samples_u + u + 1;
                vertices.push_back(uv_verts[p2]);
                norms.push_back(uv_norms[p2]);
                
                int p3 = disp + (v + 1) * samples_u + u + 1;
                vertices.push_back(uv_verts[p3]);
                norms.push_back(uv_norms[p3]);
                
                // triangle 2
                vertices.push_back(uv_verts[p1]);
                norms.push_back(uv_norms[p1]);
                
                vertices.push_back(uv_verts[p3]);
                norms.push_back(uv_norms[p3]);
                
                int p4 = disp + (v + 1) * samples_u + u;
                vertices.push_back(uv_verts[p4]);
                norms.push_back(uv_norms[p4]);
            }
        }
        disp += jump;
    }
}
