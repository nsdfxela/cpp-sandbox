#include <iostream>
#include "triangle.hpp"
#include <vector>

int main() {
  int N;
  std::cin >> N;
  std::vector<point_t> points;
  std::vector<triangle_t> triangles;
  for(int i = 0; i < N; i++){
    float x, y, z;

    std::cin >> x >> y >> z;
    points.emplace_back(x,y,z);
    if(points.size()==3){
      triangles.emplace_back(points[0], points[1], points[2]);
      points.clear();
    }
    std::cout << "triangle " << x << " " << y << " " << z << "\n";
    
  }

  return 0;
}
