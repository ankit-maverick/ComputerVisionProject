#ifndef FRAME_H
#define FRAME_H

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h> 
#include <math.h>
#include <pcl/keypoints/sift_keypoint.h>
#include <pcl/kdtree/kdtree.h>

using namespace std;
using namespace pcl;


class Frame{

	public:

		PointCloud<PointXYZRGBA>::Ptr pcdata;
		PointCloud<PointXYZRGBA>::Ptr keyPointsCloud;
		vector<PointXYZRGBA> keyPoints;

		Frame(PointCloud<PointXYZRGBA>::Ptr cloud){
			pcdata = cloud;
			extractSifftKeypoints3D();
		}

		void extractSifftKeypoints3D(){
			 const float min_scale = 0.002; 
			 const int nr_octaves = 4; 
			 const int nr_scales_per_octave = 5; 
			 const float min_contrast = 1; 
			 const float radius = 0.01; 

			 // Compute the SIFT keypoints 
			 SIFTKeypoint<PointXYZRGBA, PointWithScale> sift_detector; 
			 search::KdTree<PointXYZRGBA>::Ptr tree ((new pcl::search::KdTree<pcl::PointXYZRGBA> ())); 
			 sift_detector.setSearchMethod (tree); 
			 sift_detector.setScales (min_scale, nr_octaves, nr_scales_per_octave); 
			 sift_detector.setMinimumContrast (min_contrast); 

			 sift_detector.setSearchSurface(pcdata); 
			 sift_detector.setInputCloud(pcdata); 
			 sift_detector.setRadiusSearch (radius); 

			 PointCloud<PointWithScale> keypoints_temp; 
			 sift_detector.compute(keypoints_temp);

			 copyPointCloud(keypoints_temp, *keyPointsCloud);

			 for(int i=0; i<keypoints_temp.size; i++){
				PointXYZRGBA keyPoint = keypoints_temp.points[i];
	         keyPoints.push_back(keyPoint);
			 }
		}
}

#endif


