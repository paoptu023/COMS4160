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

typedef vec4 point4;

class Bezier{
public:
    Bezier(std::vector<point4> &pnts, int u, int v);
    
    int getUdegree() const {return u_deg;}
    int getVdegree() const {return v_deg;}
    
    std::vector<point4> getCtrCol(int u) {
        std::vector<point4> res;
        for (int i = 0; i <= v_deg; ++i)
            res.push_back(ctr_pnts[i][u]);
        return std::move(res);
    }
    
    std::vector<point4> getCtrRow(int v) {return ctr_pnts[v];}
    
    // sampling in uv space and connecting the X(u,v) values to triangles
    void sample(int sample_level, std::vector<point4> &uv_verts, std::vector<vec4> &uv_norms);
    
    // bezier surface evaluation (get final points)
    void evaluate(float t_u, float t_v, point4 &point, vec4 &norm);
    
    // evaluate in rows or columns, de Casteljau algorithm
    void eval_bez(std::vector<point4> &array, const double t, point4 &point, vec4 &tan);
    
private:
    std::vector<std::vector<point4>> ctr_pnts;
    int u_deg, v_deg;
};

#endif /* bezier_h */
