#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

class DriveBot
{
    private:
        // Create a ROS NodeHandle object
        ros::NodeHandle n_; 
        // ROS::Publisher motor commands;
        ros::Publisher motor_command_publisher;
        // Define a safe_move service with a handle_drive_request callback function
        ros::ServiceServer drive_service;

    public:
        DriveBot()
        {
            // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the 
            // robot actuation topic with a publishing queue size of 10
            motor_command_publisher = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

            // Define a command_robot service with a handle_safe_move_request callback function
            drive_service = n_.advertiseService("/ball_chaser/command_robot", &DriveBot::handle_drive_request, this);
        }

        bool handle_drive_request(ball_chaser::DriveToTarget::Request& req,
         ball_chaser::DriveToTarget::Response& res)
        {
            // Create a motor_command object of type geometry_msgs::Twist
            geometry_msgs::Twist motor_command;
            // Set wheel velocities
            motor_command.linear.x = req.linear_x;
            motor_command.angular.z = req.angular_z;
            // Publish angles to drive the robot
            motor_command_publisher.publish(motor_command);

            // Return a response message
            res.msg_feedback = "Linear velocity in X set: " + std::to_string(req.linear_x) + " , Angular yaw: " + std::to_string(req.angular_z);
            ROS_INFO_STREAM(res.msg_feedback);

            return true;
        }
};

int main(int argc, char **argv)
{
    //Initiate ROS
    ros::init(argc, argv, "drive_bot");

    //Create an object of class DriveBot that will take care of everything
    DriveBot drive;

    ros::spin();

    return 0;
}