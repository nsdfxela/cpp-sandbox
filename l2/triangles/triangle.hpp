#pragma once
#include <cmath>
struct point_t {
  float x, y, z;
  point_t(float inx, float iny, float inz) :
    x{inx}, y{iny}, z{inz}
  {}
  point_t():
    x{NAN}, y{NAN}, z{NAN}
  {};
};

class triangle_t {
protected:
  point_t  points[3];
public:
  triangle_t(const point_t &p0, const point_t &p1, const point_t &p2);

};
