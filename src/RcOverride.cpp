#include "RcOverride.h"

RcOverride::RcOverride()
{

}

RcOverride::~RcOverride()
{

}

bool RcOverride::overrideCallback(
			std_srvs::Empty::Request& request,
			std_srvs::Empty::Response& response)
{
	ROS_INFO("Hello from service callback.");
	return true;
}

void RcOverride::setOverridePublisher(ros::Publisher pub)
{
	this->override_pub = pub;
}


