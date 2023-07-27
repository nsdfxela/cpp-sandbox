#include <iostream>
#include "arc.hpp"


int main(){

  //arc::lru<int, int> lru(3);
  arc::arc<int, int> cache(4);
  
   
  std::cout << cache.toString();
  return 0;
}
