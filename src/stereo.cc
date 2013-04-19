#include "stereo.h"

void PerformStereoRegistration(){
	//Get edges
	vector<cv::Point2f> edges_left = GetEdges(source_left);
	vector<cv::Point2f> edges_right = GetEdges(source_right);

	cout << "Found " << edges_left.size() + edges_right.size() <<  " edges points.\n";

	//Mark edges on images for visualization.
	cv::Mat leftWithedges, rightWithedges;
	leftWithedges = source_left.clone();
	rightWithedges = source_right.clone();

	MarkEdges(leftWithedges, edges_left);
	MarkEdges(rightWithedges, edges_right);

	//Perform patch search for correspondences
	vector<cv::Point2f> dispVectors[3];
	GetPossibleDisparities(edges_left, edges_right, dispVectors);

	cout << "Depth for " << dispVectors[0].size() << " points computed.\n";

	//Mark correspondences on images for visualization.
	MarkCorrespondences(leftWithedges, dispVectors[1]);
	MarkCorrespondences(rightWithedges, dispVectors[2]);

	//Save marked images.
	imwrite("left_edges.png", leftWithedges);
	imwrite("right_edges.png", rightWithedges);

	//Generate sparse depth map.
	GenerateSparseDepthMap(dispVectors);

	//Save sparse depth maps.
	imwrite("left_sparseDepth.png", depth_left);
	imwrite("right_sparseDepth.png", depth_right);

	//Make depth maps dense.
	MakeDense(depth_left);
	MakeDense(depth_right);

	//Create point cloud. From now on only left image is used.
	CreatePointCloud();
}
