/*
 * RcOverride.h
 *
 *  Created on: Feb 8, 2019
 *      Author: lmark
 */

#ifndef RCOVERRIDE_H_
#define RCOVERRIDE_H_

#include "ros/ros.h"
#include "std_srvs/Empty.h"
#include "mavros_msgs/OverrideRCIn.h"

class RcOverride
{

public:

	RcOverride();
	virtual ~RcOverride();

	bool overrideCallback(
			std_srvs::Empty::Request& request,
			std_srvs::Empty::Response& response);
	void setOverridePublisher(ros::Publisher pub);

private:

	ros::Publisher override_pub;

};

#endif /* RCOVERRIDE_H_ */
