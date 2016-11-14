# Ray Tracer
A ray tracer starting from scratch in C++.

![chess](https://github.com/paoptu023/COMS4160/blob/master/chess.png=200x150)

### features:
* points, vectors, spheres, triangles, planes
* point, ambient, and area light sources
* blinn-phong lighting model
* diffuse and reflective materials
* triangle meshes (obj file format)
* axis-aligned bounding boxes and bvh trees for acceleration
* jittered monte-carlo antialiasing (smooth edges and soft shadows)
* hdr format (.exr)

### To compile: 
* mac: g++ -O2 *.cc -I. -I/usr/local/include/OpenEXR -lIlmImf -lImath -lHalf -Wall -o raytra
* linux: g++ -O2 *.cc -I. -I/usr/include/OpenEXR -lIlmImf -lImath -lHalf -Wall -o raytra

### To run: 
* ./raytra [scenefile.txt] [output.exr] [PRIMARY_NUM] [SHADOW_NUM]
