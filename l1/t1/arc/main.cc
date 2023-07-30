#include <iostream>
#include "arc.hpp"


int slowGetFunction(int key){
  std::cout << "Slow get function called for key " << key << ". Cache miss \n";
  return 42;
}
		  

int main(){

  arc::arc <int, int> arc(6);
  arc.get(3, slowGetFunction);
  arc.get(3, slowGetFunction);
  arc.get(3, slowGetFunction);
  arc.get(3, slowGetFunction);

  arc.get(12, slowGetFunction);
  arc.get(1, slowGetFunction);
  arc.get(5, slowGetFunction);
  arc.get(4, slowGetFunction);

  arc.get(5, slowGetFunction);
  arc.get(4, slowGetFunction);

  arc.get(100, slowGetFunction);
  arc.get(101, slowGetFunction);

  arc.get(12, slowGetFunction);
  arc.get(100, slowGetFunction);
  
  arc.get(14, slowGetFunction);
  arc.get(13, slowGetFunction);
  arc.get(150, slowGetFunction);
  arc.get(151, slowGetFunction);

  arc.get(12, slowGetFunction);  
  

  std::cout << arc.toString();
  //arc::lru<int, int> lru(3);
  //arc::arc<int, int> cache(4);
  /*arc::lfu<int, int> cache(5);
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

  std::cout << cache.toString();*/
    /*cache.put(1,42);
  std::cout << cache.toString();*/
  
  return 0;
}
