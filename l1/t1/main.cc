#include <iostream>
#include <string>
#include "lru.h"
#include <cassert>


int slowGetPage(int k){
  std::cout << "running slow for " << k << std::endl;
  return 42;
}
int main()
{
  std::cout << "cache:" << std::endl;
  
  int m, n;
  std::cin >> m >> n;
  std::cout << "enter data: " << std::endl;
  int hits =0;
  LruCache<int, int>* cache = new LruCache<int, int>(m);
  for(int i = 0; i < n; i++){
    int p = -1;
    std::cin >> p;
    assert(std::cin.good());
    bool result = cache->put(p, slowGetPage);
    if(result){
      ++hits;
    }
    cache->printCache();
  }
  std::cout << "hits: " << hits;

  delete cache;
  return 0;
}
