//
//  bezier.cc
//  glrender
//
//  Created by Qi Wang on 4/22/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "bezier.h"

Bezier::Bezier(vector<point4> &pnts, int u, int v){
    u_deg = u;
    v_deg = v;
    // v starts from bottom
    for (int i = v; i >= 0; --i) {
        vector<point4> row;
        for (int j = 0; j <= u; ++j){
            row.push_back(pnts[i * (u + 1) + j]);
        }
        ctr_pnts.push_back(row);
    }
}


void Bezier::sample(int sample_level, vector<point4> &uv_verts, vector<vec4> &uv_norms){
    if(sample_level >= 2){
        int samples_u = u_deg * sample_level;
        int samples_v = v_deg * sample_level;
        float spacing_u = 1.0 / (samples_u - 1);
        float spacing_v = 1.0 / (samples_v - 1);
        float t_u = 0;
        float t_v = 0;
        
        point4 point;
        vec4 norm;
        for (int i = 0; i < samples_v; ++i, t_v += spacing_v) {
            for (int j = 0; j < samples_u; ++j, t_u += spacing_u) {
                evaluate(t_v, t_u, point, norm);
                uv_verts.push_back(point);
                uv_norms.push_back(norm);
            }
        }
    }
}

// first use de Casteljau on all the rows of ctrpnts, then columns
void Bezier::evaluate(float t_v, float t_u, point4 &point, vec4 &norm){
    vector<point4> res_vctrs;
    
    vec4 tmp;
    for (int i = 0; i <= v_deg; ++i) {
        vector<point4> ctr_row = getCtrRow(i);
        point4 new_ctr;
        eval_bez(ctr_row, t_u, new_ctr, tmp);
        res_vctrs.push_back(new_ctr);
    }
    
    vec4 v_tan;
    // evaluate the resulting control points in v for final point on the surface
    eval_bez(res_vctrs, t_v, point, v_tan);
    
    vector<point4> res_uctrs;
    for (int i = 0; i <= u_deg; ++i) {
        vector<point4> ctr_col = getCtrCol(i);
        point4 new_ctr;
        eval_bez(ctr_col, t_v, new_ctr, tmp);
        res_uctrs.push_back(new_ctr);
    }
    
    point4 tmp_pnt; vec4 u_tan;
    eval_bez(res_uctrs, t_u, tmp_pnt, u_tan);
    
    // frenet frame
    norm = normalize(vec4(cross(v_tan, u_tan), 0.0));
}


/* evaluate in rows or columns, de Casteljau algorithm
 * br,i = (1 − t) * br−1,i + t * br−1,i+1
 * 00
 * 01 10
 * 02 11 20
 * 03 12 21 30
 * [0 0]
 * [0 2] [0 1]
 * [8 2] [4 2] [2 1.5]
 * [4 0] [6 1] [5 1.5] [3.5 1.5]
 */
void Bezier::eval_bez(vector<point4> &array, const double t, point4 &point, vec4 &tan){
    int degree = (int) array.size() - 1;
    // overwrite the array
    point4 prev, cur;
    for (int i = 0; i < degree; ++i) {
        prev = array[i];
        for (int j = i + 1; j <= degree; ++j) {
            cur = (1 - t) * prev + t * array[j];
            prev = array[j];
            array[j] = cur;
        }
    }
    
    // cur is the point at parameter value t on the nth-degree bezier curve
    point = cur;
    // b21 - b20, b21 is stored in prev (overwrited by b30)
    tan = prev - array[degree - 1];
}
