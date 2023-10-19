#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include <iostream>
#include <math.h>

const float WHEEL_RADIUS = 12.5 / 100;

class SpeedCalcNode : public rclcpp::Node
{
    public:
        SpeedCalcNode() : Node("hello_world_sub_node") {
            rpm_subscription_ = this->create_subscription<std_msgs::msg::Float64>(
                "rpm", 10, std::bind(&SpeedCalcNode::calculate_and_pub_speed, this, std::placeholders::_1)
            );
            speed_publisher_ = this->create_publisher<std_msgs::msg::Float64>(
                "speed", 10
            );
            std::cout << "Speed Calc Node is Running" << "\n";
        }
    private:
        void calculate_and_pub_speed(const std_msgs::msg::Float64& rpm_msg) const {
            auto speed_msg = std_msgs::msg::Float64();
            speed_msg.data = rpm_msg.data * (2 * WHEEL_RADIUS * M_PI) / 60;
            speed_publisher_->publish(speed_msg);
        }
        rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr rpm_subscription_;
        rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr speed_publisher_;
};
int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SpeedCalcNode>());
    rclcpp::shutdown();
    return 0;
}