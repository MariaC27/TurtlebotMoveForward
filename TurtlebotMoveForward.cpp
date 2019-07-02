#include <ros/ros.h>
#include <tf/tf.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_listener.h>
#include <actionlib/server/simple_action_server.h>
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/PointStamped.h" 

// Function declarations 
void update_endpoints(const geometry_msgs::PointStamped::ConstPtr& msg); 
void move_turtlebot(double x, double y, double yaw); 
void callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg); 

// Global variables for the two endpoints 
double first_x = -1;
double first_y = -1;
double second_x = -1;
double second_y = -1; 
int seq_counter = 0; 

int main(int argc, char **argv)
{ 
	ros::init(argc, argv, "patrolling_turtle"); 
	ros::NodeHandle n;

	// Subscribes to two topics
	ros::Subscriber sub = n.subscribe("test1", 1000, update_endpoints); 

	ros::Subscriber sub2 = n.subscribe("test2", 1000, callback); 
	
	ros::spin();
}

// Name: update_endpoints
// Parameters: pointer to geometry_msgs::PointStamped
// Does: updates the global points between which the robot will patrol
//	and once they are declared, sends the robot to the first one
void update_endpoints(const geometry_msgs::PointStamped::ConstPtr& msg)
{ 

	

		ROS_INFO("Thank you! Beginning patrol now...\n"); 
		move_turtlebot(first_x, first_y, 0.0); 
		
	

}

// Name: move_turtlebot
// Parameters: x,y coordinates and an angle
// Does: sends a message to move the robot to the given x,y spot and 
//	face in the given direction
// Note: assumes a 2-D grid, thus z is always 0
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

// Name: callback
// Parameters: pointer to geometry_msgs::PoseWithCovarianceStamped
// Does: checks to see which point the robot is closest to and then goes to the opposite point
// Note: currently all orientations are set to 0.0, but that is arbitrary 
void callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
		
			move_turtlebot(first_x, first_y, 0.0); 
		
		
}