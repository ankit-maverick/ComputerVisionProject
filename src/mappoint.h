#ifndef MAPPOINT_H
#define MAPPOINT_H

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

using namespace pcl;

class MapPoint{

	public: 
		int matched_freq;
		PointXYZRGBA point;

		MapPoint(PointXYZRGBA point_data, int m_freq)
		{
			matched_freq = m_freq;
			point = point_data;
		}

};

#endif
