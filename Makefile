.PHONY: all clean

all: main libdmz.so
	python setup.py build_ext --inplace

libdmz.so:
	c++ -fPIC -DCYTHON_DMZ -DSCAN_EXPIRY -Idmz -I/usr/include/python2.7/ -I/usr/include/opencv -L/usr/lib/x86_64-linux-gnu -l:libopencv_core.so.2.4 -l:libopencv_imgproc.so.2.4 -shared dmz/dmz_all.cpp -o libdmz.so

main: libdmz.so
	c++ main.cpp -o main -Idmz -L./ -ldmz -lopencv_core -lopencv_imgproc -lopencv_highgui

clean:
	rm -rf main cardio.cpp cardio.so libdmz.so build
