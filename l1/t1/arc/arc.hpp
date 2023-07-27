#pragma once
#include <list>
#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <sstream>

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

  }


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
