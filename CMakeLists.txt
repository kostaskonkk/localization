cmake_minimum_required(VERSION 2.8.3)
project(localization)
add_compile_options(-std=c++11)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  tf
  cmake_modules REQUIRED
  barc
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${barc_INCLUDE_DIRS}
)

add_executable(odometry_node src/odometry.cpp)
target_link_libraries(odometry_node ${catkin_LIBRARIES})
