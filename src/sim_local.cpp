#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>


void odomCallback(const nav_msgs::Odometry msg){
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  transform.setOrigin( tf::Vector3(msg.pose.pose.position.x, msg.pose.pose.position.y, 0.0) );
  tf::Quaternion q( 0,0,msg.pose.pose.orientation.z,msg.pose.pose.orientation.w);
  //q.setRPY(0, 0, msg->theta);
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), msg.header.frame_id, msg.child_frame_id));
}

int main(int argc, char** argv){
  ros::init(argc, argv, "sim_local");
  //if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
  //turtle_name = argv[1];

  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("ego_pose", 10, &odomCallback);

  ros::spin();
  return 0;
};
