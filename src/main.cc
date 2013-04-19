#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <pthread.h>
#include <sched.h>

#include "stereo.h"
#include "tracker.h"
#include "map.h"
#include "main.h"

using namespace std;
//using namespace cv;

cv::Mat source_left, source_right, depth_left, depth_right;

bool shouldCap = true;

void StartMapping(){

	#ifdef __linux__
		cpu_set_t mask;
		int status;

		CPU_ZERO(&mask);
		CPU_SET(MAPPING_CPU, &mask);
		status = sched_setaffinity(0, sizeof(mask), &mask);

		if (status != 0)
			perror("sched_setaffinity");
	#endif	

	HandleMap();
}

void StartTracking(){
	#ifdef __linux__
		cpu_set_t mask;
		int status;

		CPU_ZERO(&mask);
		CPU_SET(TRACKER_CPU, &mask);
		status = sched_setaffinity(0, sizeof(mask), &mask);

		if (status != 0)
			perror("sched_setaffinity");
	#endif	
	
	TrackFrame();
}

int main(){

	#ifdef __linux__
		cpu_set_t mask;
		int status;

		CPU_ZERO(&mask);
		CPU_SET(STEREO_CPU, &mask);
		status = sched_setaffinity(0, sizeof(mask), &mask);

		if (status != 0)
			perror("sched_setaffinity");
	#endif

	boost::thread_group tgroup;
	tgroup.create_thread(boost::bind(&StartMapping));	
	tgroup.create_thread(boost::bind(&StartTracking));

	while(1){//For each incoming frame.	

		//Load images
		source_left = cv::imread(SOURCE_LEFT, 1);
		source_right = cv::imread(SOURCE_RIGHT, 1);

		//Register images.
		PerformStereoRegistration();
	}

	return 0;
}	
	
