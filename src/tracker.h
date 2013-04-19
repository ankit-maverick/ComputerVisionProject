#ifndef TRACKER_H
#define TRACKER_H

//PCL Includes.
#include <Eigen/Core>

//OpenCV Includes.
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <opencv/cv.h>

//General Includes.
#include <iostream>
#include <math.h>

#include "stereo.h"
#include "map.h"

//Feature extraction
#define maxCorners	2000
#define qualityLevel	0.01
#define minDistance	10

#define discountFactor 0.8

using namespace std;
//using namespace cv;
using namespace Eigen;

extern Matrix4f cameraPose, cameraPose_old, cameraPose_old2;
extern vector<cv::Point2f> features;

void TrackFrame();
void MarkFeatures(cv::Mat, vector<cv::Point2f>);
Matrix4f ApplyMotionModel();

#endif
