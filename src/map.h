#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h> 
#include <math.h>

#include <boost/thread.hpp>
#include <boost/date_time.hpp>

#include "mappoint.h"
#include "keyframe.h"

using namespace std;
using namespace pcl;

class Map{

	public:
		PointCloud<PointXYZRGBA>::Ptr mapCloud;
		vector<int> matched_freq;
		int state_no;

		Map()
		{
		     state_no = 0;
	  		  PointCloud<PointXYZRGBA>::Ptr newCloud (new PointCloud<PointXYZRGBA>);
			  mapCloud = newCloud;
		}

		 // Update the map with new KeyFrame object as the input, check and update(weighted)
		 // correspondence MapPoints for keyPoints that exist in the Map and add them 
		 // if they don't match with any existing MapPoint
		 
		void update_map(KeyFrame newKF)
		{

			state_no = state_no + 1;

			for (int i = 0; i < newKF.keyPoints.size(); i++)
			{	
				float min_distance = -1.0;
				int min_index = 0;
		         
		      // TODO : value of threshold --> decide while testing
				float threshold = 10;

				// include normalised rgb distance  

				float x1 = newKF.keyPoints[i].x;
				float y1 = newKF.keyPoints[i].y;
				float z1 = newKF.keyPoints[i].z;
			
				Eigen::Vector3i rgbVec = newKF.keyPoints[i].getRGBVector3i();

				int b1 = (int)rgbVec[0];
				int g1 = (int)rgbVec[1];
				int r1 = (int)rgbVec[2];

				// calculate distance and update min_distance and min_index
				for (int j = 0; j < mapCloud->size(); j++)
				{
					float x2 = mapCloud->points[j].x;
					float y2 = mapCloud->points[j].y;
					float z2 = mapCloud->points[j].z;

					float dist = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) + (z1 - z2)*(z1 - z2));

					if (dist < min_distance || min_distance<0)
					{
						min_distance = dist;
						min_index = j;
					}
				}
		         
				if (min_distance < threshold)
				{

					 // update mapPoints[min_index]'s XYZRGBA value
		             
					Eigen::Vector3i rgbVec = mapCloud->points[min_index].getRGBVector3i();

					int b2 = (int)rgbVec[0];
					int g2 = (int)rgbVec[1];
					int r2 = (int)rgbVec[2];

		         int weight = matched_freq[min_index];
		             
					mapCloud->points[min_index].x = (weight*mapCloud->points[min_index].x + newKF.keyPoints[i].x)/(weight + 1);
					mapCloud->points[min_index].y = (weight*mapCloud->points[min_index].y + newKF.keyPoints[i].y)/(weight + 1);
					mapCloud->points[min_index].z = (weight*mapCloud->points[min_index].z + newKF.keyPoints[i].z)/(weight + 1);
		             
					Eigen::Vector3i rgbVec2;
	
					rgbVec2[0]  = (weight*b2 + b1)/(weight + 1);
	            rgbVec2[1]  = (weight*g2 + g1)/(weight + 1);
	            rgbVec2[2]  = (weight*r2 + r1)/(weight + 1);

					mapCloud->points[min_index].getRGBVector3i() = rgbVec2; 
			
	            matched_freq[min_index] += 1; 
				}

				else
				{
		         MapPoint new_mapPoint(newKF.keyPoints[i], 1);                
					mapCloud->points.push_back(new_mapPoint.point);
					matched_freq.push_back(1);
				}

			}

		}
};

void HandleMap();

extern int lastPoppedKF = 0;
extern queueOfKF* KFQueue;
extern bool ready = false;

#endif

