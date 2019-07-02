#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
ros::Publisher velocity_publisher; 
ros::Subscriber pose_subscriber;
turtlesim::Pose turtlesim_pose;

const double x_min = 0.0;
const double y_min = 0.0;
const double x_max = 11.0;
const double y_max = 11.0;

const double PI = 3.1415926;

//method to move the robot straight forward

void move(double speed, double distance, bool isForward);

int main (int argc, char **argv){
    ros::init(argc, argv, "turtle_move_forward");
    ros::NodeHandle n;
    double speed = 2;
    double angular_speed;
    double distance = 2;
    double angle;
    bool isForward = true;
    bool clockwise;

    velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    ros::Rate loop_rate(10);

    ROS_INFO("\n\n\n******STARTING******\n");
    
    move(speed, distance, isForward);

    ros::spin();

    return 0;
}

void move (double speed, double distance, bool isForward){
    geometry_msgs::Twist vel_msg;

    if (isForward){
        vel_msg.linear.x = abs(speed);
    }

    else {
        vel_msg.linear.x = -abs(speed);
    }

    vel_msg.linear.y = 0;
    vel_msg.linear.z = 0;
    vel_msg.angular.x = 0;
    vel_msg.angular.y = 0;
    vel_msg.angular.z = 0;


double t0 = ros::Time::now().toSec();
double current_distance = 0.0;
ros::Rate loop_rate(100);

do{
    velocity_publisher.publish(vel_msg);
    double t1 = ros::Time::now().toSec();
    current_distance = speed * (t1-t0);
    ros::spinOnce();
    loop_rate.sleep();
}

    

    while(current_distance<distance);
    vel_msg.linear.x = 0;
    velocity_publisher.publish(vel_msg);


}