cmake_minimum_required(VERSION 2.8.3)
project(localization)
add_compile_options(-std=c++11)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  tf
  cmake_modules REQUIRED
  barc
)
catkin_package()
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${barc_INCLUDE_DIRS}
)

add_executable(odometry_node src/odometry.cpp)
target_link_libraries(odometry_node ${catkin_LIBRARIES})

add_executable(robot_localization_node src/robot_local.cpp)
target_link_libraries(robot_localization_node ${catkin_LIBRARIES})

add_executable(mocap_local src/mocap_local.cpp)
target_link_libraries(mocap_local ${catkin_LIBRARIES})
