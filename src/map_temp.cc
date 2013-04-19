#include <map.h>

//using namespace cv;
using namespace std;
using namespace pcl;

/*
    Instantiating these classes and calling their methods from the Tracking module should be like --
    
    Map myMap = Map();
    
	if some_condition is True:  // current_frame is a keyframe
    {
		Keyframe newKF = KeyFrame(int serial_no, Mat abs_RT_matrix, PointCloud<PointXYZRGBA> data);
		
		// this will create a vector of keypoints and store them in newKF.keypoints
		newKF.get_keypoints(PointCloud<PointXYZRGBA> pcdata, vector<PointXYZRGBA> keyPoints, Mat abs_RT);
		
		myMap.update_map( newKF );
    
    }
*/

// Sift KeyPoint detector. Called in KeyFrame.get_keypoints() . Will need to change the detector parameters after testing

PointCloud<PointXYZRGBA>::Ptr extractSifftKeypoints3D(PointCloud<PointXYZRGBA>::Ptr cloud) 
{ 
    
    const float min_scale = 0.002; 
    const int nr_octaves = 4; 
    const int nr_scales_per_octave = 5; 
    const float min_contrast = 1; 
    const float radius = 0.01; 

    // Compute the SIFT keypoints 
    SIFTKeypoint<PointXYZRGBA, PointWithScale> sift_detector; 
    search::KdTree<PointXYZRGBA>::Ptr tree (new search::KdTree<PointXYZRGBA>); 
    sift_detector.setSearchMethod (tree); 
    sift_detector.setScales (min_scale, nr_octaves, nr_scales_per_octave); 
    sift_detector.setMinimumContrast (min_contrast); 

    sift_detector.setSearchSurface(cloud); 
    sift_detector.setInputCloud(cloud); 
    sift_detector.setRadiusSearch (radius); 

    PointCloud<PointWithScale> keypoints_temp; 
    sift_detector.compute(keypoints_temp); 

    PointCloud<PointXYZRGBA>::Ptr keypoints(new PointCloud<PointXYZRGBA>); 
    copyPointCloud (keypoints_temp, *keypoints); 

    return(keypoints);

}





