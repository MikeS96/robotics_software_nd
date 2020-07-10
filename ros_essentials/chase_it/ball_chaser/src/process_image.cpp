#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

class ChaseBall
{
    private:
        // Create a ROS NodeHandle object
        ros::NodeHandle n_; 
        // ROS::Publisher motor commands;
        ros::Subscriber image_subscriber;
        // Define a safe_move service with a handle_drive_request callback function
        ros::ServiceClient drive_client;

    public:
        ChaseBall()
        {
            // Define a client service capable of requesting services from command_robot
            drive_client = n_.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

            // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
            image_subscriber = n_.subscribe("/camera/rgb/image_raw", 10, &ChaseBall::process_image_callback, this);
        }

        // This function calls the command_robot service to drive the robot in the specified direction
        void drive_robot(float lin_x, float ang_z)
        {

            // Request Linear X and Angular Z
            ball_chaser::DriveToTarget srv;
            srv.request.linear_x = lin_x;
            srv.request.angular_z = ang_z;

            // Call the safe_move service and pass the requested joint angles
            if (!drive_client.call(srv))
                ROS_ERROR("Failed to call service command_robot");
        }

        // This callback function continuously executes and reads the image data
        void process_image_callback(const sensor_msgs::Image img)
        {

            int white_pixel = 255;
            int row;
            bool pixel_found = false;
            float lin_x, ang_z;

            // Loop through each pixel in the image and check if there's a bright white one
            for (int i = 0; i < img.height * img.step; i += 3) {
                if (img.data[i] == white_pixel) 
                {
                    // Obtain the current row value
                    row = i % img.step;
                    pixel_found = true;
                    break;
                }
            }

            if (pixel_found == true)
            {
                // Identify if this pixel falls in the left, mid, or right side of the image
                if (row < img.step / 3) 
                {
                    // Turn Left
                    lin_x = 0.0;
                    ang_z = 0.3;
                }
                else if (row > img.step * 2 / 3) 
                {
                    // Turn Right
                    lin_x = 0.0;
                    ang_z = -0.3;
                }
                else 
                {
                    // Move Forward
                    lin_x = 0.5;
                    ang_z = 0.0;
                }
            }
            // Request a stop when there's no white ball seen by the camera
            else
            {
                // Stop
                lin_x = 0.0;
                ang_z = 0.0;
            }
            
            // Depending on the white ball position, call the drive_bot function and pass velocities to it
            ChaseBall::drive_robot(lin_x, ang_z);
        }

};

int main(int argc, char **argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");

    //Create an object of class DriveBot that will take care of everything
    ChaseBall chaser;

    ros::spin();

    return 0;
}
