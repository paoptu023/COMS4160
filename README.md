# Ray Tracer

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
