#include "robot_local.hpp"

Localization::Localization(){
    robot_1_sub= n.subscribe("/robot_1", 1, &Localization::robot_1_callback, this);
    robot_2_sub= n.subscribe("/robot_2", 1, &Localization::robot_2_callback, this);

    robot_1_pub=n.advertise<geometry_msgs::PoseStamped>("/robot_1_with_frame",10);
    robot_2_pub=n.advertise<geometry_msgs::PoseStamped>("/robot_2_with_frame",10);
    new_msg.header.frame_id = "map";
    
  }


void Localization::robot_1_callback(const geometry_msgs::PoseStamped& msg){
  new_msg.pose = msg.pose;
  robot_1_pub.publish(new_msg);
}

void Localization::robot_2_callback(const geometry_msgs::PoseStamped& msg){
  new_msg.pose = msg.pose;
  robot_2_pub.publish(new_msg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "robot_localization_node");
  Localization local_object;
  ros::spin();

  return 0;
}
