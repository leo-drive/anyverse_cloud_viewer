#ifndef LEOPAR_POINTANYVERSE_H
#define LEOPAR_POINTANYVERSE_H
#define PCL_NO_PRECOMPILE

#include <pcl/pcl_macros.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>

struct PointAnyverse {
  PCL_ADD_POINT4D;
  uint8_t r0;
  uint8_t g0;
  uint8_t b0;

  uint8_t r1;
  uint8_t g1;
  uint8_t b1;

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
} EIGEN_ALIGN16;

POINT_CLOUD_REGISTER_POINT_STRUCT (PointAnyverse,
                                   (float, x, x)
                                     (float, y, y)
                                     (float, z, z)
                                     (float, r0, r0)
                                     (float, g0, g0)
                                     (float, b0, b0)
                                     (float, r1, r1)
                                     (float, g1, g1)
                                     (float, b1, b1)
)



//    # .PCD v0.7 - Point Cloud Data file format
//    VERSION 0.7
//    FIELDS x y z r0 g0 b0 r1 g1 b1
//    SIZE 4 4 4 1 1 1 1 1 1
//    TYPE F F F U U U U U U
//    COUNT 1 1 1 1 1 1 1 1 1
//    WIDTH 21661
//    HEIGHT 1
//    VIEWPOINT 0 0 0 1 0 0 0
//    POINTS 21661
//    DATA binary


#endif //LEOPAR_POINTANYVERSE_H
