#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h> 
#include <pcl/keypoints/sift_keypoint.h>
#include <math.h>

using namespace std;
using namespace pcl;
//using namespace cv;

class KeyFrame{

	public:

		int index;                      // SEerial no of KeyFrame
		cv::Mat abs_RT;                     // Absolute RT matrix for keyframe
		PointCloud<PointXYZRGBA>::Ptr pcdata;// keyframe pointclouddATA
		vector<PointXYZRGBA> keyPoints; // vector keyPoints
		 
		KeyFrame(int serial_no, cv::Mat abs_RT_matrix, PointCloud<PointXYZRGBA>::Ptr data)
		 {

			index = serial_no;
			abs_RT = abs_RT_matrix;
			pcdata = data;

		}
		 
		void get_keypoints()
		 {
		     
		     //Apply SIFT KeyPoint Detector on this KeyFrame
			extractSifftKeypoints3D();      


		     // Changing current xyz of keyPoints to world-coordinates
			for (int i = 0; i < keyPoints.size(); i++)
			{  
		         // Create a Vector holding xyz co-ordinates
				float xyzdata[4][1] = {{keyPoints[i].x},{keyPoints[i].y},{keyPoints[i].z},1};
				cv::Mat xyz(4, 1, CV_32FC1, xyzdata);
		         
				cv::Mat abs_xyz = abs_RT.inv()*xyz;
		         
				keyPoints[i].x = abs_xyz.at<float>(0,0);
				keyPoints[i].y = abs_xyz.at<float>(1,0);
				keyPoints[i].z = abs_xyz.at<float>(2,0);
		         
			}
		     
		}

		void extractSifftKeypoints3D(){
			const float min_scale = 0.002; 
			 const int nr_octaves = 4; 
			 const int nr_scales_per_octave = 5; 
			 const float min_contrast = 1; 
			 const float radius = 0.01; 

			 // Compute the SIFT keypoints 
			 SIFTKeypoint<PointXYZRGBA, PointXYZRGBA> sift_detector; 
			 search::KdTree<PointXYZRGBA>::Ptr tree (new search::KdTree<PointXYZRGBA>()); 
			 sift_detector.setSearchMethod (tree); 
			 sift_detector.setScales (min_scale, nr_octaves, nr_scales_per_octave); 
			 sift_detector.setMinimumContrast (min_contrast); 

			 sift_detector.setSearchSurface(pcdata); 
			 sift_detector.setInputCloud(pcdata); 
			 sift_detector.setRadiusSearch (radius); 

			 PointCloud<PointXYZRGBA> keypoints_temp; 
			 sift_detector.compute(keypoints_temp); 

			 PointCloud<PointXYZRGBA>::Ptr keypoints(new PointCloud<PointXYZRGBA>); 
			 copyPointCloud (keypoints_temp, *keypoints); 

			  for(int i=0; i<keypoints_temp.size(); i++)
			  {
			      PointXYZRGBA keyPoint = keypoints_temp.points[i];
			      keyPoints.push_back(keyPoint);
			  } 
		}
};

struct node                                                
{            
	KeyFrame KF;
  node* nextNode;
}; 

struct queueOfKF
{
	node* firstNode;
	int size;
};

#endif
