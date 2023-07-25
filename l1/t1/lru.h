#pragma once
#include <unordered_map>
#include <list>
#include <iostream>

template<typename K, typename V>
class LruCache {

 public:
 LruCache(int capacity):capacity_{capacity}{
  }
  template<typename F>
  bool put(K key, F func){
    auto mapIt = searchMap.find(key);
    if(mapIt == searchMap.end()){
      //check if have capacity. pop back if no.
      
      if(capacity_ == cache.size()){
	searchMap.erase(cache.back().first);
	cache.pop_back();
      }
      //add to list, add to map
      cache.emplace_front(key, func(key));
      searchMap.emplace(key, cache.begin());
      return false;
    } else {
      auto cacheIt = mapIt->second;
      //remove from list, push to front of list
      if(cacheIt != cache.begin()){
	cache.splice(cache.begin(), cache, cacheIt);
      }
      return true;
    }
  }
  void printCache(){
    for(auto it = cache.begin(); it != cache.end(); ++it){
      std::cout << it->first << " ";
    }
    std::cout << std::endl;
  }
protected:
  using ListIt = typename std::list<std::pair<K,V>>::iterator;
  std::list<std::pair<K,V>> cache;
  std::unordered_map<K, ListIt> searchMap;
  int capacity_;
};
