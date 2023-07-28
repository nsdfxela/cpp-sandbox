#pragma once
#include <list>
#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <sstream>
#include <map>

namespace arc {
  template<typename K, typename V>
  struct lru
  {
    using list_t = typename std::list<std::pair<K,V>>;
    std::unordered_map<K, typename list_t::iterator> map;
    std::list<std::pair<K,V>> cache;
    int capacity;
    int size() const{
      return capacity;
    }
    lru(int cap):capacity{cap}
    {
      
    }
    lru():capacity{0}{}
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
    std::string toString(){
      std::stringstream sstr;
      for(auto it = cache.begin(); it != cache.end(); ++it){
	sstr << it->first << " ";
      }
      sstr << std::endl;
      return sstr.str();
    }
    void put(K key, V val){
      assert(!contains(key));
      if(cache.size() == capacity){
	map.erase(cache.back().first);
	cache.pop_back();
      }
      cache.emplace_front(key, val);
      map.emplace(key, cache.begin());
    }
    
    V get(K key){
      assert(contains(key));
      moveFront(key);
      return map.find(key)->second->second;
    }
  };

  template<typename K, typename V>
  struct lfu
  {
    int capacity;
    using entry = typename std::pair<K, V>;
    using entryFreq = std::pair<int, entry>;
    using entryIt = typename std::list<entryFreq>::iterator;
    std::unordered_map<K, entryIt> map;
    std::list<entryFreq> cache;
    bool contains(K key){
      return (map.find(key) != map.end());
    }
    void put(K key, V val)
    {
      assert(!contains(key));
      if(cache.size() == capacity){
	map.erase(cache.back().first);
	cache.pop_back();
      }

      cache.emplace_back(0, std::make_pair(key, val));
      auto lastElementIt = std::prev(cache.end());
      map.emplace(key, lastElementIt);
    }
    V get(K key)
    {
      assert(contains(key));
      auto eit = map.find(key)->second; //entryIt
      eit->first += 1; //frequency++
      if(eit != cache.begin()){
	auto prevIt = std::prev(eit);
	if(prevIt->first < eit->first){ //eit met more frequently than the neighbor, lets move it
	  cache.splice(prevIt, cache, eit);
	}
      }
      
      return eit->second.second;
    }
    lfu(int cap) : capacity{cap} { }
    std::string toString(){
      std::stringstream ss;
      for(auto it = cache.begin(); it != cache.end(); it++){
	ss << "k:" << it->second.first << " f:" << it->first << ", ";
      }
      ss << std::endl;
      return ss.str();
    }
  };


  template<typename K, typename V>
  struct arc
  {
    int capacity;
    //int t1_cap, t2_cap;
    lru<K,V> t1, t2;
    lru<K,int> b1, b2;
    arc(int cap) : capacity{cap},
		   t1{cap/2},
		   t2{cap-cap/2},
		   b1{cap/2},
		   b2{cap-cap/2}
    {
            
    }

    
    
    std::string toString(){
      std::stringstream ss;

      ss << "t1 size " << t1.size() << ":" << t1.toString();
      ss << "t2 size " << t2.size() << ":" << t2.toString();
      return ss.str();
    }
    
  };
}
