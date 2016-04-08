# COMS4160
Computer Graphics 
ray tracer

To compile: 
* mac: g++ -O2 *.cc -I. -I/usr/local/include/OpenEXR -lIlmImf -lImath -lHalf -Wall -o raytra
* linux: g++ -O2 *.cc -I. -I/usr/include/OpenEXR -lIlmImf -lImath -lHalf -Wall -o raytra

To run: 
* ./raytra [scenefile.txt] [output.exr] [PRIMARY_NUM] [SHADOW_NUM]
