#include "odometry.hpp"

Odometry::Odometry(){
    sub_steering = n.subscribe("/rc_inputs", 1, &Odometry::ecu_callback, this);
    sub_wheel_speeds = n.subscribe("/wheel_speeds", 1, &Odometry::wheel_speeds_callback, this);
    twist_pub=n.advertise<geometry_msgs::TwistWithCovarianceStamped>("/odometry",10);
    velocity.header.frame_id = "base_link";
    velocity.twist.covariance = {3, 0, 0, 0, 0, 0,
				                         0, 3, 0, 0, 0, 0,
				                         0, 0, 50, 0, 0, 0,
				                         0, 0, 0, 50, 0, 0,
				                         0, 0, 0, 0, 50, 0,
				                         0, 0, 0, 0, 0, 50};
  }

void Odometry::ecu_callback(const barc::ECU& ecu){

  if (not_first_callback && time > ros::Time::now()){
    time = ros::Time::now();
    not_first_callback = false;
}
  double steering_input = ecu.servo;
  //Saturation
  if(steering_input > 115) steering_input = 115;
  else if(steering_input < 65) steering_input = 65;

  if(not_first_callback == true){
    double dt = (ros::Time::now() - time).toSec();
    time = ros::Time::now();

    double f = (-integral + steering_input) / (0.035 + DBL_EPSILON); 

    if (f > 380) f = 380;
    else if ( f<-380) f =-380;

    integral += f * dt;
    delta = integral * -0.01008 + 0.9021;// values taken from Baars
  }
  else if(not_first_callback == false){
    time = ros::Time::now();
    not_first_callback = true;
    integral = steering_input; //initialisation of integrator
  }
}

void Odometry::wheel_speeds_callback(const barc::Encoder& ws){

  if(not_first_callback){
    double front_omega = (ws.FL + ws.FR)/2;
    //double rear_omega = (ws.BL + ws.BR)/2;
    double vel = front_omega * 0.0313; // Wheel radius?

    velocity.header.stamp = ros::Time::now();
    velocity.twist.twist.linear.x = vel * cos(delta);
    velocity.twist.twist.linear.y = vel * sin(delta);
    twist_pub.publish(velocity);
  }

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "odom_node");
  Odometry odom_object;
  ros::spin();

  return 0;
}
