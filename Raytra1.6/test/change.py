import sys

if (len(sys.argv) < 2):
	print "input format: python change.py <file_name>"
	exit()

new_obj = open("new_obj.txt", "w+")
for l in open(sys.argv[1]):
	if l[0] != 'f':
		new_obj.write(l)
		continue
	f, x, y, z = l[:-1].split(' ')
	new_obj.write("f {} {} {}\n".format(x, z, y))

new_obj.close()

