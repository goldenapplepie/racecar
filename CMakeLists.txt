cmake_minimum_required(VERSION 2.8.3)
project(racecar)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp geometry_msgs sensor_msgs)

## Declare ROS messages and services
#add_message_files(FILES Num.msg)
#add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
#generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
#include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(racecar_talker src/racecar_controller.cpp)
target_link_libraries(racecar_talker ${catkin_LIBRARIES})
#add_dependencies(talker beginner_tutorials_generate_messages_cpp)
