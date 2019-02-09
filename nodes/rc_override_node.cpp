#include "RcOverride.h"

/**
 *	Main override node.
 */
int main (int argc, char **argv)
{
	ros::init(argc, argv, "rc_override_node");
	ros::NodeHandle nh;

	RcOverride rcOverride;
	ros::Publisher overridePub = nh.advertise<mavros_msgs::OverrideRCIn>(
			"/mavros/rc/override", 1);
	ros::ServiceServer service_srv = nh.advertiseService(
			"override_service",
			&RcOverride::overrideCallback,
			&rcOverride);

	rcOverride.setOverridePublisher(overridePub);

	while(nh.ok())
	{
		ros::spin();
	}

	return 0;
}
