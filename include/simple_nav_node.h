
#ifndef SIMPLE_NAV_H
#define SIMPLE_NAV_H

#include <rclcpp/rclcpp.hpp>
#include "nav_msgs/srv/get_map.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"
#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;
using std::placeholders::_1;

class SimpleNav : public rclcpp::Node
{
  public:
    SimpleNav();
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr goal_subscriber_;
    rclcpp::Subscription<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr initial_pose_subscriber_;

    void goalCallback(const geometry_msgs::msg::PoseStamped::SharedPtr msg) const;
    void initialPoseCallback(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg) const;
};

#endif

