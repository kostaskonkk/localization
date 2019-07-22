#include "ros/ros.h"
#include <geometry_msgs/TwistWithCovarianceStamped.h>
#include <barc/ECU.h>
#include <barc/Encoder.h>

using namespace std;

class Odometry
{
public:
  Odometry();

  void ecu_callback(const barc::ECU& );
  void wheel_speeds_callback(const barc::Encoder& );

private:
  ros::NodeHandle n; 
  ros::Subscriber sub_steering;
  ros::Subscriber sub_wheel_speeds;
  ros::Publisher twist_pub;

  geometry_msgs::TwistWithCovarianceStamped velocity;
  double delta;
  bool not_first_callback = false;
  double integral = 0;
  ros::Time time;

};




