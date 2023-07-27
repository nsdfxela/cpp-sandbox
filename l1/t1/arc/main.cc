#include <iostream>
#include "arc.hpp"


int main(){

  arc::lru<int, int> lru(3);
  
  std::cout << "arc\n";
  return 0;
}
