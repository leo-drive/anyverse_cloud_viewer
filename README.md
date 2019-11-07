# Anyverse Cloud Viewer

## How build and run

```
mkdir -p ~/catkin_ws/src && cd ~/catkin_ws/src
git clone https://github.com/leo-muhendislik/anyverse_cloud_viewer.git
cd ..
catkin_make
source devel/setup.bash

# either run the launch file with customs parameters
roslaunch anyverse_cloud_viewer anyverse_cloud_viewer.launch path_lidar_point_cloud:=your_path/lidar-highway/lidar-highway-routeA/lidar-point-cloud rviz:=true

# or edit the launch file defaults and run it without parameters
roslaunch anyverse_cloud_viewer anyverse_cloud_viewer.launch
```