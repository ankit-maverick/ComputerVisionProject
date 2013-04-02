CC = g++
COMPILEFLAGS = -I /usr/local/include -D_LINUX -D_REENTRANT -Wall  -O3 -march=nocona -msse3

LINKFLAGS = -L /usr/local/lib -L /usr/lib/x86_64-linux-gnu -lopencv_core -lopencv_highgui -lopencv_flann -lopencv_objdetect -lopencv_video -lopencv_videostab -lopencv_ts -lopencv_features2d -lopencv_contrib -lopencv_calib3d -lopencv_gpu -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_photo -lopencv_stitching


OBJECTS=	main.o\
			features.o\
			patch.o\
			depth.o

All: STEREO

STEREO: $(OBJECTS)
	$(CC) -o run $(OBJECTS) $(LINKFLAGS)


%.o: %.cc
	$(CC) $< -o $@ -c $(COMPILEFLAGS)

clean:
	rm *.o


depend:
	rm dependecies; touch dependencies
	makedepend -fdependencies $(INCLUDEFLAGS) $(MOREINCS) *.cc *.h


-include dependencies









