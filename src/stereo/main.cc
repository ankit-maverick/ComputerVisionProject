#include "stereo.h"

using namespace std;
using namespace cv;

Mat source_left, source_right, depth_left, depth_right;

int main(){

	//Load images
	source_left = imread(SOURCE_LEFT, 1);
	source_right = imread(SOURCE_RIGHT, 1);

/*	//Uncomment this section, comment out edge detection and change similarityThreshold to ~40 in stereo.h to use goodFeaturesToTrack
	//Extract features
	vector<Point2f> features_left = ExtractFeatures(source_left);
	vector<Point2f> features_right = ExtractFeatures(source_right);
*/

	//Get edges
	vector<Point2f> features_left = GetEdges(source_left);
	vector<Point2f> features_right = GetEdges(source_right);

	cout << features_left.size() << " features extracted successfully!\n";
	
	//cout << features_left;
	//Mark features on images for visualization.
	Mat leftWithFeatures, rightWithFeatures;
	leftWithFeatures = source_left.clone();
	rightWithFeatures = source_right.clone();

	MarkFeatures(leftWithFeatures, features_left);
	MarkFeatures(rightWithFeatures, features_right);

	//Perform patch search for correspondences
	vector<Point2f> dispVectors[3];
	GetPossibleDisparities(features_left, features_right, dispVectors);

	cout << "Depth for " << dispVectors[0].size() << " points computed.\n";

	//Mark correspondences on images for visualization.
	MarkCorrespondences(leftWithFeatures, dispVectors[1]);
	MarkCorrespondences(rightWithFeatures, dispVectors[2]);

	//Save marked images.
	imwrite("left_features.png", leftWithFeatures);
	imwrite("right_features.png", rightWithFeatures);

	//Generate sparse depth map.
	GenerateSparseDepthMap(dispVectors);

	//Save sparse depth maps.
	imwrite("left_sparseDepth.png", depth_left);
	imwrite("right_sparseDepth.png", depth_right);

	//Make depth maps dense.
	MakeDense(depth_left);
	MakeDense(depth_right);

	return 0;
}	
	
