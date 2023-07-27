#pragma once
#include <list>
#include <algorithm>
#include <cassert>
#include <unordered_map>

namespace arc {
  template<typename K, typename V>
  struct lru
  {
    using list_t = typename std::list<std::pair<K,V>>;
    std::unordered_map<K, typename list_t::iterator> map;
    std::list<std::pair<K,V>> cache;
    int capacity;
    
    lru(int cap):capacity{cap}
    {
      
    }
    bool contains(K key){
      return map.find(key) != map.end();
    }
  protected:
    void moveFront(K key){
      auto iter = map.find(key)->second;
      if(iter != cache.begin()){
	cache.splice(cache.begin(), cache, iter);
      }
    }
  public:
    V get(K key){
      assert(contains(key));
      moveFront(key);
      return map.find(key)->second;
    }
    

   

  };

  

}
