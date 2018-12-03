cmake_minimum_required(VERSION 2.8.3)
project(stepper_driver)
set(CMAKE_CXX_STANDARD 11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  )

catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
  )

include_directories(
  ${catkin_INCLUDE_DIRS}
  )

## Declare a cpp executable
add_executable(stepper_driver src/stepper_driver.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(stepper_driver
  ${catkin_LIBRARIES}
  wiringPi
  )
