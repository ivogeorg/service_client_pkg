#include "iri_wam_reproduce_trajectory/ExecTraj.h"
#include "ros/package.h"
#include "ros/ros.h"

int main(int argc, char **argv) {
  // Initialise a named ROS node
  ros::init(argc, argv, "execute_trajectory_client");
  ros::NodeHandle nh;

  // Create the connection to the service /execute_trajectory

  // wait for service to be running
  ros::service::waitForService("/execute_trajectory");

  ros::ServiceClient exec_traj_service =
      nh.serviceClient<iri_wam_reproduce_trajectory::ExecTraj>(
          "/execute_trajectory");

  // create ExecTraj object for service call argument
  iri_wam_reproduce_trajectory::ExecTraj trajectory;

  // request requires a filename, populate it
  // available trajectory files: get_food.txt, init_pos.txt, release_food.txt
  trajectory.request.file =
      ros::package::getPath("iri_wam_reproduce_trajectory") +
      "/config/get_food.txt";

  // Send through the connection the name of the trajectory to execute
  if (exec_traj_service.call(trajectory)) {
    // no specific response, so just report success
    ROS_INFO("Service successfully called. Executing trajectory.");
  } else {
    ROS_ERROR("Failed to call service /execute_trajectory");
    return 1;
  }

  return 0;
}