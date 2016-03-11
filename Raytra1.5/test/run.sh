for i in 1.0 1.05 1.1 1.15 1.2 1.25 1.3 1.35 1.4 1.45 1.5;

do
cp lol.txt lol1.txt
echo on frame $i
echo m 0 .1 .2 .5 .5 .5 100 .1 .2 .3 >> lol1.txt
echo t -500 $i -500 -500 $i 500 500 $i 500 >> lol1.txt
echo t 500 $i 500 500 $i -500 -500 $i -500 >> lol1.txt

./raytra lol1.txt gifs/wee$i.exr
rm -f lol1.txt;

done