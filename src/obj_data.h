#ifndef OBJ_DATA_H
#define OBJ_DATA_H

#include <array>
#include <vector>

namespace s21 {

struct DataObj {
  std::vector<double> vertexes;
  std::vector<unsigned int> facets;
  unsigned int count_vertex;
  unsigned int count_facets;
  unsigned int count_edges;
};

struct Transform {
  int axis;
  double value;
  double prev_angle_x;
  double prev_angle_y;
  double prev_angle_z;

  std::array<double, 3> prev_coor;
};

enum Axis {kX, kY, kZ};

}  // namespace s21

#endif  // OBJ_DATA_H