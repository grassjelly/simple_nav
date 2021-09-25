#include <simple_nav_node.h>

SimpleNav::SimpleNav()
  : Node("simple_nav")
{
  rclcpp::Client<nav_msgs::srv::GetMap>::SharedPtr map_server_client =
    this->create_client<nav_msgs::srv::GetMap>("map_server/map");

  auto map_request = std::make_shared<nav_msgs::srv::GetMap::Request>();

  while (!map_server_client->wait_for_service(1s)) 
  {
    if (!rclcpp::ok()) 
    {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = map_server_client->async_send_request(map_request);
  if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result) == rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Map loaded.");
    // result.get()->map.data[-1];
  } 
  else 
  {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to load map from the map server.");
  }

  goal_subscriber_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
  "goal_pose", 10, std::bind(&SimpleNav::goalCallback, this, _1));

  initial_pose_subscriber_ = this->create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
  "initialpose", 10, std::bind(&SimpleNav::initialPoseCallback, this, _1));
}

void SimpleNav::goalCallback(const geometry_msgs::msg::PoseStamped::SharedPtr msg) const
{
  RCLCPP_INFO(this->get_logger(), "GOAL X: '%f' GOAL Y: '%f'", msg->pose.position.x, msg->pose.position.y);
}

void SimpleNav::initialPoseCallback(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg) const
{
  RCLCPP_INFO(this->get_logger(), "GOAL X: '%f' GOAL Y: '%f'", msg->pose.pose.position.x, msg->pose.pose.position.y);
}