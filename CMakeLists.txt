cmake_minimum_required(VERSION 3.5)
project(anyverse_cloud_viewer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -O3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g3 -O3")

find_package(catkin REQUIRED COMPONENTS
        geometry_msgs
        nav_msgs
        sensor_msgs
        roscpp
        rospy
        std_msgs
        tf
        tf_conversions
        pcl_ros
        )
find_package(PCL REQUIRED)

catkin_package(
        CATKIN_DEPENDS
        geometry_msgs
        nav_msgs
        roscpp
        rospy
        std_msgs
        pcl_ros
)


include_directories(
        ${Boost_INCLUDE_DIR}
        ${catkin_INCLUDE_DIRS}
        ${PCL_INCLUDE_DIRS}
        include
)

add_executable(${PROJECT_NAME}_exec
        src/main.cpp
        )

target_link_libraries(${PROJECT_NAME}_exec
        ${Boost_LIBRARIES}
        ${catkin_LIBRARIES}
        ${PCL_LIBRARIES}
        )

add_dependencies(${PROJECT_NAME}_exec ${catkin_EXPORTED_TARGETS})
