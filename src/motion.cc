#include "tracker.h"

Matrix4f ApplyMotionModel(Eigen::Matrix4f prevMotion){
	currExpMotion = prevMotion*discountFactor;

	return currExpMotion;
}

Matrix4f UpdateMotionModel(Eigen::Matrix4f currentPose, Eigen::Matrix4f prevPose){
	prevMotion = currentPose/prevPose;

	return prevMotion;
}

