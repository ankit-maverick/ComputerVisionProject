CC = g++
COMPILEFLAGS = -I /usr/local/include -I /usr/local/include/pcl-1.7 -I /usr/local/include/pcl-1.7/pcl -I /usr/include/eigen3 -I /usr/include/vtk-5.8 -D_LINUX -D_REENTRANT -Wall  -O3 -march=nocona -msse3

LINKFLAGS = -L /usr/local/lib -L /usr/lib/x86_64-linux-gnu -lopencv_core -lopencv_highgui -lopencv_flann -lopencv_objdetect -lopencv_video -lopencv_videostab -lopencv_ts -lopencv_features2d -lopencv_contrib -lopencv_calib3d -lopencv_gpu -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_photo -lopencv_stitching -lGL -lpthread -lpcl_2d -lpcl_apps -lpcl_common -lpcl_cuda_features -lpcl_cuda_io -lpcl_cuda_sample_consensus -lpcl_cuda_segmentation -lpcl_features -lpcl_filters -lpcl_gpu_containers -lpcl_gpu_features -lpcl_gpu_kinfu -lpcl_gpu_kinfu_large_scale -lpcl_gpu_octree -lpcl_gpu_people -lpcl_gpu_segmentation -lpcl_gpu_surface -lpcl_gpu_tracking -lpcl_gpu_utils -lpcl_io -lpcl_io_ply -lpcl_kdtree -lpcl_keypoints -lpcl_octree -lpcl_ml -lpcl_outofcore -lpcl_recognition -lpcl_registration -lpcl_sample_consensus -lpcl_search -lpcl_segmentation -lpcl_stereo -lpcl_surface -lpcl_tracking -lpcl_visualization -lvtkalglib -lvtkCharts -lvtkCommon -lvtkDICOMParser -lvtkexoIIc -lvtkFiltering -lvtkftgl -lvtkGenericFiltering -lvtkGeovis -lvtkGraphics -lvtkHybrid -lvtkImaging -lvtkInfovis -lvtkIO -lvtkmetaio -lvtkParallel -lvtkproj4 -lvtkQtChart -lvtkRendering -lvtksys -lvtkverdict -lvtkViews -lvtkVolumeRendering -lvtkWidgets -lboost_date_time -lboost_date_time-mt -lboost_filesystem -lboost_filesystem-mt -lboost_iostreams -lboost_iostreams-mt -lboost_regex -lboost_regex-mt -lboost_serialization -lboost_serialization-mt -lboost_system -lboost_system-mt -lboost_thread -lboost_thread-mt -lboost_wserialization -lboost_wserialization-mt -lX11


OBJECTS=	main.o\
			patch.o\
			depth.o\
			cloud.o\
			tracker.o\
			features.o\
			stereo.o\
			edges.o\
			motion.o\
			icp.o\
			map.o\
			
			

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









