#include "stereo.h"


//Go through all features of the left image and try to find correspondences in the right image.
void GetPossibleDisparities(vector<Point2f> features_left, vector<Point2f> features_right, vector<Point2f>* returnList){
	
	vector<Point2f> dispVector;	//Will store disparities.
	vector<Point2f> leftCorrs;		//Will store source of disparity points in left image.
	vector<Point2f> rightCorrs;	//Will store source of disparity points in right image.

	for(unsigned int i=0; i<features_left.size(); i++){		
		for(int j=0; j<features_right.size(); j++){
			Point2f left, right;
			left.x = features_left[i].x;
			left.y = features_left[i].y;
			right.x = features_right[j].x;
			right.y = features_right[j].y;

			//Search for correspondences within a window.
			if(abs(left.x - right.x) < windowSize_x){
				if(abs(left.y - right.y) < windowSize_y){
					unsigned char* left_ptr = source_left.ptr<unsigned char>(features_left[i].y);
					unsigned char* right_ptr = source_right.ptr<unsigned char>(features_right[j].y);

					unsigned char b_error = abs(left_ptr[(int)(3*features_left[i].x)] - right_ptr[(int)(3*features_right[j].x)]);
					unsigned char g_error = abs(left_ptr[(int)(3*features_left[i].x + 1)] - right_ptr[(int)(3*features_right[j].x + 1)]);
					unsigned char r_error = abs(left_ptr[(int)(3*features_left[i].x + 2)] - right_ptr[(int)(3*features_right[j].x + 2)]);
					
					//Check if intensities at both the points are similar.
					if(b_error<similarityThreshold && g_error<similarityThreshold && r_error<similarityThreshold){
						Point2f disparity;
						disparity.x = features_left[i].x - features_right[j].x;
						disparity.y = features_left[i].y - features_right[j].y;

						//Update lists.
						dispVector.push_back(disparity);
						leftCorrs.push_back(features_left[i]);
						rightCorrs.push_back(features_right[j]);
					}
				}	
			}
		}
	}

	returnList[0] = dispVector;
	returnList[1] = leftCorrs;
	returnList[2] = rightCorrs;
}


//Mark correspondences in blue on images for visualization.
void MarkCorrespondences(Mat img, vector<Point2f> corrs){
	for(int k=0; k<corrs.size(); k++){
		int point_x = corrs[k].x;
		int point_y = corrs[k].y;
	
		for(int i=-1; i<2; i++){
			for(int j=-1; j<2; j++){
				int currentX = point_x + j;
				int currentY = point_y + i;
				
				//Check for out of range accesses.
				if(currentX>=img.size().width || currentY>=img.size().height || (abs(i)+abs(j))==2 || currentX<0 || currentY<0)	
					continue;
	
				unsigned char* img_ptr = img.ptr<unsigned char>(currentY);
				img_ptr[3*currentX]=255;
				img_ptr[3*currentX + 1]=0;
				img_ptr[3*currentX + 2]=0;
			}
		}
	}
}
