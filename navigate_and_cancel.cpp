#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <nav2_msgs/action/navigate_to_pose.hpp>

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);

  // Creating a ROS 2 node
  auto node = rclcpp::Node::make_shared("cancel_nav_goals_node");

  // Creating an action client for the "navigate_to_pose" action
  auto cancel_navto_client = rclcpp_action::create_client<nav2_msgs::action::NavigateToPose>(
    node, "/navigate_to_pose"
  );

  // Wait for the action server to become available
  if (!cancel_navto_client->wait_for_action_server(std::chrono::seconds(5))) {
    RCLCPP_ERROR(node->get_logger(), "Action server not available");
    return 1;
  }

  // Cancel all goals
  cancel_navto_client->async_cancel_all_goals();

  RCLCPP_INFO(node->get_logger(), "Cancelled all navigation goals");

  rclcpp::shutdown();
  return 0;
}

