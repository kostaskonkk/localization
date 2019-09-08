#include "ros/ros.h"
#include <geometry_msgs/PoseStamped.h>
using namespace std;

class Localization
{
public:
  Localization();

  void robot_1_callback(const geometry_msgs::PoseStamped& );
  void robot_2_callback(const geometry_msgs::PoseStamped& );

private:
  ros::NodeHandle n; 
  ros::Subscriber robot_1_sub;
  ros::Subscriber robot_2_sub;
  ros::Publisher robot_1_pub;
  ros::Publisher robot_2_pub;

  geometry_msgs::PoseStamped new_msg;

};




