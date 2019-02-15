/*
 * MpcToPx4Command.cpp
 *
 *  Created on: Jun 23, 2017
 *      Author: thaus
 */


#include "MpcToPx4Command.h"

MpcToPx4Command::MpcToPx4Command():
  thrust_max_(25)
{
    // TODO Auto-generated constructor stub
}

MpcToPx4Command::~MpcToPx4Command() {
	// TODO Auto-generated destructor stub
}

void MpcToPx4Command::setPx4AttitudeCmdPublisher(ros::Publisher attitude_cmd_pub) {
  px4_attitude_cmd_pub_ = attitude_cmd_pub;
}

void MpcToPx4Command::setPx4ThrustCmdPublisher(ros::Publisher thrust_cmd_pub) {
  px4_thrust_cmd_pub_ = thrust_cmd_pub;
}

void MpcToPx4Command::setPx4AngularVelCmdPublisher(ros::Publisher angular_vel_cmd_pub) {
  px4_angular_vel_cmd_pub_ = angular_vel_cmd_pub;
}

void MpcToPx4Command::setMaxThrust(float thrust_max) {
  thrust_max_ = thrust_max;
}


void MpcToPx4Command::mpcCmdCallback(const mav_msgs::RollPitchYawrateThrust &msg) {

  mavros_msgs::Thrust thrust_msg;
  mavros_msgs::AttitudeTarget attitude_msg;
  geometry_msgs::TwistStamped twist_msg;

  // from the thrust message just use z component and scale to 0-1
  double thrust_value = msg.thrust.z / thrust_max_;

  if (thrust_value > 1.0) {
	  thrust_value = 1.0;
  }
  else if (thrust_value < 0.0) {
	  thrust_value = 0.0;
  }

  thrust_msg.thrust = thrust_value;

  //transform roll, pitch , yaw to quaternion
  // to ensure bumpless transfer between different modes for yaw use measured yaw (from imu)
  tf::Quaternion quaternion;
  quaternion.setEulerZYX(yaw_imu_, msg.pitch, msg.roll);

  attitude_msg.header = msg.header;
  attitude_msg.type_mask = 7;

  attitude_msg.orientation.x = quaternion.x();
  attitude_msg.orientation.y = quaternion.y();
  attitude_msg.orientation.z = quaternion.z();
  attitude_msg.orientation.w = quaternion.w();

  attitude_msg.body_rate.x = 0;
  attitude_msg.body_rate.y = 0;
  attitude_msg.body_rate.z = 0;

  attitude_msg.thrust = thrust_value;

  twist_msg.header = msg.header;
  twist_msg.twist.linear.x = 0;
  twist_msg.twist.linear.y = 0;
  twist_msg.twist.linear.z = 0;

  twist_msg.twist.angular.x = 0;
  twist_msg.twist.angular.y = 0;
  twist_msg.twist.angular.z = -msg.yaw_rate;

  // px4_thrust_cmd_pub_.publish(thrust_msg);
  px4_attitude_cmd_pub_.publish(attitude_msg);
  // px4_angular_vel_cmd_pub_.publish(twist_msg);

}

void MpcToPx4Command::imuCallback(const sensor_msgs::Imu &msg) {

  double roll, pitch, yaw;
  // transform quaternion to euler
  tf::Quaternion quaternion_imu(msg.orientation.x, msg.orientation.y, msg.orientation.z, msg.orientation.w);
  tf::Matrix3x3 m(quaternion_imu);
  m.getRPY(roll, pitch, yaw);
  yaw_imu_ = yaw;

}
