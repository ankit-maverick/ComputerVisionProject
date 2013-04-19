#ifndef STEREO_H
#define STEREO_H

#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <opencv/cv.h>
#include <iostream>
#include <math.h>

//Loading image
#define SOURCE_LEFT	"source_left.png"
#define SOURCE_RIGHT	"source_right.png"
#define imgWidth source_left.size().width
#define imgHeight source_left.size().height

//Edge detection
#define lowThreshold 60
#define max_lowThreshold 100
#define ratio 3
#define kernel_size 3

//Correspondence search
#define windowSize_x 50
#define windowSize_y 5
#define similarityThreshold 5

//Depth Map
#define baseline 10
#define focalLength 10

using namespace std;
//using namespace cv;

extern cv::Mat source_left, source_right, depth_left, depth_right;

void GetPossibleDisparities(vector<cv::Point2f>, vector<cv::Point2f>, vector<cv::Point2f>*);
vector<cv::Point2f> ExtractFeatures(cv::Mat);
void MarkEdges(cv::Mat, vector<cv::Point2f>);
void MarkCorrespondences(cv::Mat, vector<cv::Point2f>);
void GenerateSparseDepthMap(vector<cv::Point2f>*);
vector<cv::Point2f> GetEdges(cv::Mat);
void MakeDense(cv::Mat);
void CreatePointCloud();
void PerformStereoRegistration();

#endif //STEREO_H
