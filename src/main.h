#ifndef MAIN_H
#define MAIN_H

#define STEREO_CPU 0%boost::thread::hardware_concurrency()
#define TRACKER_CPU 1%boost::thread::hardware_concurrency()
#define MAPPING_CPU 2%boost::thread::hardware_concurrency()


#endif
