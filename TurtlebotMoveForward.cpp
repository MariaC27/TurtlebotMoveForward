#include <ros/ros.h>
#include <tf/tf.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_listener.h>
#include <actionlib/server/simple_action_server.h>
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/PointStamped.h" 
ros::Publisher velocity_publisher; 
ros::Subscriber pose_subscriber;
turtlesim::Pose turtlesim_pose;


//method to move the robot straight forward

void move(double speed, double distance, bool isForward);

int main (int argc, char **argv){
    ros::init(argc, argv, "turtle_move_forward");
    ros::NodeHandle n;
    

    velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    ros::Rate loop_rate(10);

    ROS_INFO("\n\n\n******STARTING******\n");
    
    move_turtlebot(2.0, 2.0, 0.0);

    ros::spin();

    return 0;
}

void move_turtlebot(double x, double y, double yaw)
{
	actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);

                ac.waitForServer();
                move_base_msgs::MoveBaseGoal goal;

                goal.target_pose.header.stamp = ros::Time::now();
            	goal.target_pose.header.frame_id = "/map";

		goal.target_pose.pose.position.x = x;
		goal.target_pose.pose.position.y = y;
		goal.target_pose.pose.position.z = 0.0;  
		goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
		ac.sendGoal(goal);
		ac.waitForResult(); 

}
