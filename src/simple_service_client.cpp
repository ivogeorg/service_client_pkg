#include "ros/ros.h"
#include "trajectory_by_name_srv/TrajByName.h"
// Import the service message used by the service /trajectory_by_name

int main(int argc, char **argv) {
  // Initialise a ROS node with the name service_client
  //   ros::init(argc, argv, "service_client");
  ros::init(argc, argv, "simple_service_client");
  ros::NodeHandle nh;

  // Create the connection to the service /trajectory_by_name

  // wait for service to be running
  ros::service::waitForService("/trajectory_by_name");

  ros::ServiceClient traj_by_name_service =
      nh.serviceClient<trajectory_by_name_srv::TrajByName>(
          "/trajectory_by_name");

  trajectory_by_name_srv::TrajByName srv; // Create an object of type TrajByName

  // Fill the variable traj_name with the desired value
  srv.request.traj_name = "release_food";

  // Send through the connection the name of the trajectory to execute
  if (traj_by_name_service.call(srv)) {
    // Print the result given by the service called
    ROS_INFO("%s", srv.response.status_message.c_str());
  } else {
    ROS_ERROR("Failed to call service /trajectory_by_name");
    return 1;
  }

  return 0;
}