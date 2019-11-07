#include "PointAnyverse.h"
#include <pcl/io/pcd_io.h>
#include <iostream>
#include <ros/ros.h>
#include <boost/filesystem.hpp>
#include <vector>
#include <algorithm>
#include "alphanum.h"
#include "HelperRosRelated.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "anyverse_cloud_viewer_node");
  ros::NodeHandle nh("~");

  std::string path_folder;
  nh.getParam("path_lidar_point_cloud", path_folder);

  ros::Publisher pub_cloud = nh.advertise<sensor_msgs::PointCloud2>(
    "/cloud_anyverse", 1);

  using namespace boost::filesystem;

  if (!is_directory(path_folder)) {
    std::cout << path_folder << " is not a directory." << std::endl;
    return -1;
  }

  std::vector<path> vec_unordered_dirs;
  std::copy(directory_iterator(path_folder), directory_iterator(), std::back_inserter(vec_unordered_dirs));

  std::vector<std::string> vec_ordered_dirs;
  std::transform(vec_unordered_dirs.begin(), vec_unordered_dirs.end(), std::back_inserter(vec_ordered_dirs),
                 [](const path &c) -> std::string { return c.string(); });

  std::sort(vec_ordered_dirs.begin(), vec_ordered_dirs.end(), doj::alphanum_less<std::string>());

  // print pcd file paths to be read
  std::cout << path_folder << " is a directory containing:" << std::endl;
  for (std::vector<std::string>::const_iterator it(vec_ordered_dirs.begin()); it != vec_ordered_dirs.end(); ++it) {
    std::cout << "   " << *it << '\n';
  }

  // publishing rate
  ros::Rate rate(10);

  for (const auto &path : vec_ordered_dirs) {
    // read with custom point format
    using CloudAnyverse = pcl::PointCloud<PointAnyverse>;
    CloudAnyverse::Ptr cloud_anyverse(new CloudAnyverse);

    if (pcl::io::loadPCDFile<PointAnyverse>(path, *cloud_anyverse) == -1) {
      PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
      return (-1);
    }

    using PointRGB = pcl::PointXYZRGB;
    using CloudRGB = pcl::PointCloud<PointRGB>;

    // convert it into standard pcl::PointXYZRGB
    CloudRGB::Ptr cloud_rgb(new CloudRGB);
    std::transform(cloud_anyverse->points.begin(), cloud_anyverse->points.end(), std::back_inserter(cloud_rgb->points),
                   [](const PointAnyverse &p) -> PointRGB {
                     PointRGB point;
                     point.x = p.x;
//                     point.y = p.y;
//                     point.z = p.z;
                     point.y = p.z; // dirty axis fix
                     point.z = p.y; // dirty axis fix
                     point.r = p.r0;
                     point.g = p.g0;
                     point.b = p.b0;
                     return point;
                   });

    HelperRosRelated::PublishCloud<pcl::PointXYZRGB>(*cloud_rgb, pub_cloud, ros::Time::now(), "base_link");
    ros::spinOnce();
    rate.sleep();
  }
  return 0;
}