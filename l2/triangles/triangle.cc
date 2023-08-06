#include "triangle.hpp"

triangle_t::triangle_t(const point_t &p0, const point_t &p1, const point_t &p2){
  points [0] = p0;
  points [1] = p1;
  points [2] = p2;
}
