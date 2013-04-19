#include "map.h"
#include "tracker.h"
#include <pcl/registration/icp.h>

using namespace pcl;
//using namespace cv;
using namespace std;
using namespace Eigen;

Matrix4f realCamPose = ICP(Matrix4f roughCamPose, Frame, currFrame, Map map){

	IterativeClosestPoint<PointXYZRGBA, PointXYZRGBA> icp;

	icp.setInputCloud(currFrame.keyPointsCloud);
	icp.setInputTarget(map.mapCloud);

	PointCloud<PointXYZRGBA> Final;

	icp.align(Final);

	return icp.getFinalTransformation();
}
