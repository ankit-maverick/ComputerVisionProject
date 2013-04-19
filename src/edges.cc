#include "stereo.h"


//Mark edges on images in red for visualization.
void MarkEdges(cv::Mat img, vector<cv::Point2f> edges){
	for(int k=0; k<edges.size(); k++){
		int point_x = edges[k].x;
		int point_y = edges[k].y;
		for(int i=-1; i<2; i++){
			for(int j=-1; j<2; j++){
				int currentX = point_x + j;
				int currentY = point_y + i;

				//Check for out of range accesses.
				if(currentX>=imgWidth || currentY>=imgHeight || (abs(i)+abs(j))==2 || currentX<0 || currentY<0)
					continue;

				unsigned char* img_ptr = img.ptr<unsigned char>(currentY);
				img_ptr[3*currentX]=0;
				img_ptr[3*currentX + 1]=0;
				img_ptr[3*currentX + 2]=255;
			}
		}
	}
}


vector<cv::Point2f> GetEdges(cv::Mat img_src){
	cv::Mat src_gray, edges;
	cvtColor(img_src, src_gray, CV_BGR2GRAY);	//Convert to grayscale.
	
	blur(src_gray, edges, Size(3,3));	//Blur image for better edge detection.
	
	Canny(edges, edges, lowThreshold, lowThreshold*ratio, kernel_size);		//Edge detection.

	vector<cv::Point2f> edgesVector;

	for(int x=0; x<edges.size().width; x++){
		for(int y=0; y<edges.size().height; y++){
			uchar* rowPointer = edges.ptr<uchar>(y); 
			if((unsigned int)rowPointer[x]>0){
				cv::Point2f edgePoint;
				edgePoint.x = x;
				edgePoint.y = y;
				edgesVector.push_back(edgePoint);
			}
		}
	}
	
	imwrite("edge.png", edges);

	return edgesVector;
}









