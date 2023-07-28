#include <iostream>
#include "arc.hpp"


int main(){

  //arc::lru<int, int> lru(3);
  //arc::arc<int, int> cache(4);
  arc::lfu<int, int> cache(5);
  cache.put(1,42);
  cache.put(2,42);
  cache.put(3,42);
  cache.put(4,42);
  cache.put(5,42);
  std::cout << cache.toString();
  cache.get(1);
  cache.get(1);
  cache.get(1);
  cache.get(1);
  cache.get(2);
  cache.get(2);
  std::cout << cache.toString();
  cache.get(5);
  cache.get(5);
  cache.get(5);
  cache.get(5);
  cache.get(5);
  std::cout << cache.toString();
  cache.put(7,42);
  cache.get(7);
  cache.get(7);
  cache.get(7);
  cache.get(7);
  cache.get(7);
  cache.get(7);

  std::cout << cache.toString();
    /*cache.put(1,42);
  std::cout << cache.toString();*/
  
  return 0;
}
