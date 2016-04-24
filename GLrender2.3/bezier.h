//
//  bezier.h
//  glrender
//
//  Created by Qi Wang on 4/22/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef bezier_h
#define bezier_h

#include <stdio.h>
#include "amath.h"
#include <vector>
using namespace std;

typedef vec4 point4;

class Bezier{
public:
    Bezier(vector<point4> &pnts, int u, int v);
    
    int getUdegree() const {return u_deg;}
    int getVdegree() const {return v_deg;}
    
    vector<point4> getCtrCol(int u) {
        vector<point4> res;
        for (int i = 0; i <= v_deg; ++i)
            res.push_back(ctr_pnts[i][u]);
        return std::move(res);
    }
    
    vector<point4> getCtrRow(int v) {return ctr_pnts[v];}
    
    // sampling in uv space and connecting the X(u,v) values to triangles
    void sample(int sample_level, vector<point4> &uv_verts, vector<vec4> &uv_norms);
    
    // bezier surface evaluation (get final points)
    void evaluate(float t_u, float t_v, point4 &point, vec4 &norm);
    
    // evaluate in rows or columns, de Casteljau algorithm
    void eval_bez(vector<point4> &array, const double t, point4 &point, vec4 &tan);
    
private:
    vector<vector<point4>> ctr_pnts;
    int u_deg, v_deg;
};

#endif /* bezier_h */
