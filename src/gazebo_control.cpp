// 用于控制gazebo里面的小车运动

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <termios.h>
#include <stdio.h>

char getch() {
    struct termios oldt, newt;
    char c;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "gazebo_control");
    ros::NodeHandle nh;
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    
    geometry_msgs::Twist msg;
    
    ROS_INFO("Use 'w' to move forward, 's' to move backward, 'a' to turn left, 'd' to turn right, 'x' to stop.");
    
    while (ros::ok()) {
        char c = getch();
        switch (c) {
            case 'w': // 前进
                msg.linear.x = 3.0; // 调整速度，可以自己设置，下同
                msg.angular.z = 0;
                break;
            case 's': // 后退
                msg.linear.x = -3.0; // 调整速度
                msg.angular.z = 0;
                break;
            case 'a': // 向左转
                msg.linear.x = 0;
                msg.angular.z = 3.0; // 调整速度
                break;
            case 'd': // 向右转
                msg.linear.x = 0;
                msg.angular.z = -3.0; // 调整速度
                break;
            case 'x': // 停止
                msg.linear.x = 0;
                msg.angular.z = 0;
                break;
            default:
                continue;
        }
        cmd_vel_pub.publish(msg);
        ros::spinOnce();
    }
    return 0;
}
