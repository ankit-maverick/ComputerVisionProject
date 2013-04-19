#include "tracker.h"

vector<cv::Point2f> features;
Eigen::Matrix4f prevMotion = Eigen::Matrix4f::Identity(), prevPose;
node* currentNode;

void CheckForKF(Frame currFrame, Matrix4f camPose, counter){
	if(counter%30==0){
		currentNode = new node;
		KFQueue->size ++;

		cv::Mat camPose_MAT(4, 4);

		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				camPose_MAT.at<float>(4, 4) = camPose(i, j);
			}
		}

		Keyframe tempKF(KFQueue->size, camPose_MAT, currFrame.pcdata);
	}
}
void TrackFrame(){

	queueOfKF* KFQueue;
	KFQueue->size = 0;
	KFQueue->firstNode = NULL;

	node* currentNode = firstNode;

	int counter = 0;

	bool ready = true;

	while(1){
		Frame currFrame(currCloud);

		//Get rough pose estimate from motion model.
		Matrix4f roughCamPose = ApplyMotionModel(prevMotion);	
	
		Matrix4f realCamPose = ICP(roughCamPose, currFrame, map);

		prevMotion = UpdateMotionModel(realCamPose, prevPose);
	
		counter++;

		CheckForKF(currFrame, realCamPose, counter);
	}
}
