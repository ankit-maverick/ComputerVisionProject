#include "stereo.h"

void GenerateSparseDepthMap(vector<Point2f>* dispVectors){

	depth_left = Mat::zeros(source_left.size().height, source_left.size().width, CV_32F);
	depth_right = Mat::zeros(source_right.size().height, source_right.size().width, CV_32F);

	for(int i=0; i<dispVectors[0].size(); i++){
		float disparity = fabs(sqrt(dispVectors[0][i].x*dispVectors[0][i].x + dispVectors[0][i].y*dispVectors[0][i].y));
		float depth = (baseline*focalLength)/disparity;
		
		for(int ix=-1; ix<2; ix++){
			for(int iy=-1; iy<2; iy++){
				int currentX_left = dispVectors[1][i].x + ix;
				int currentX_right = dispVectors[2][i].x + ix;
				int currentY_left = dispVectors[1][i].y + iy;
				int currentY_right = dispVectors[2][i].y + iy;

				if(currentX_left<imgWidth && currentY_left<imgHeight && (abs(ix)+abs(iy))!=2 && currentX_left>=0 && currentY_left>=0){
					depth_left.at<float>(currentX_left, currentY_left) = depth;
				}			
				if(currentX_right<imgWidth && currentY_right<imgHeight && (abs(ix)+abs(iy))!=2 && currentX_right>=0 && currentY_right>=0){
					depth_right.at<float>(currentX_right, currentY_right) = depth;
				}
			}
		}
	}
}


void MakeDense(Mat depthMap){
	
	
}







