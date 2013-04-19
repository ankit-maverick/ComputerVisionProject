#include "main.h"
#include "map.h"

void HandleMap(){

	while(!ready){
		boost::this_thread::sleep(boost::posix_time::seconds(1));
	}

	Map map();
	lastNode = KFQueue->firstNode;

	while(ready){
		if(lastPoppedKF==KFQueue->size){
			boost::this_thread::sleep(boost::posix_time::seconds(1));		
			continue;
		}

		lastNode = lastNode->nextNode;

		map.update_map(lastNode->KF);
		
	}

}
