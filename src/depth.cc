#include "stereo.h"
#include <math.h>

void GenerateSparseDepthMap(vector<cv::Point2f>* dispVectors){

	depth_left = cv::Mat::zeros(source_left.size().height, source_left.size().width, CV_32F);
	depth_right = cv::Mat::zeros(source_right.size().height, source_right.size().width, CV_32F);

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


void MakeDense(cv::Mat depthMap){

	interpolated_Depth = cv::Mat::zeros(depthMap.size().height, depthMap.size().width, CV_32F);

	int m = depthMap.size().height/8;
	int n = depthMap.size().width/8;

	for (int i = 0; i < depthMap.size().height, i++)
	{
		for (int j = 0; j < depthMap.size().width, j++)
		{
			if (depthMap.at<float>(i, j) != 0)
			{
				interpolated_Depth.at<float>(i, j) = depthMap.at<float>(i, j);
			}

			else
			{
				int p = i - m/2;
				int q = j - n/2;
				int r = i + m/2;
				int s = j + n/2;

				if (p < 0){ p = 0;}
				if (q < 0){ q = 0;}
				if (r > depthMap.size().height){ r = depthMap.size().height;}
				if (s > depthMap.size().width){ s = depthMap.size().width;}

				int weight_sum = 0;
				int depth_sum = 0;

				for ( int a = p; a < r; a++)
				{
					for (int b = q; b < s; b++)
					{
						if (depthMap.at<float>(a, b) != 0)
						{
							int weight = exp(2*(-(i-a)*(i-a) - (j-b)(j-b))/sqrt(m*m + n*n));
							weight_sum += weight;
							depth_sum += weight*depthMap.at<float>(i, j);

						}

					}
				}

				interpolated_Depth.at<float>(i, j) = depth_sum/weight_sum;
			}
		}
	}

	
	
}







