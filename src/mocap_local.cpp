#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/PoseStamped.h>

//std::string turtle_name;



void poseCallback(const geometry_msgs::PoseStamped& msg){
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  transform.setOrigin( tf::Vector3(msg.pose.position.x, msg.pose.position.y, 0.0) );
  tf::Quaternion q( 0,0,msg.pose.orientation.z,msg.pose.orientation.w);
  //q.setRPY(0, 0, msg->theta);
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "base_link"));
}

int main(int argc, char** argv){
  ros::init(argc, argv, "mocap_local");
  //if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
  //turtle_name = argv[1];

  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("mocap_pose", 10, &poseCallback);

  ros::spin();
  return 0;
};
