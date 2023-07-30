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
      return cache.size();
    }
    bool isFull() const {
      return size() == capacity;
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
	evict();
      }
      cache.emplace_front(key, val);
      map.emplace(key, cache.begin());
    }
    
    V get(K key){
      assert(contains(key));
      moveFront(key);
      return map.find(key)->second->second;
    }
    std::pair<K,V> evict(){
      assert(cache.size());
      auto result = cache.back();
      map.erase(cache.back().first);      
      cache.pop_back();      
      return result;
    }
    std::pair<K,V> evict(K key){
      auto found = map.find(key);
      assert(found != map.end());
      auto result = *(found->second);
      map.erase(result.first);      
      cache.erase(found->second);      
      return result;
    }
    void decCapacity(){

      if(capacity > 0){
	capacity -= 1;
      }
      assert(size() <= capacity);
    }
    void incCapacity(){
      capacity+=1;
    }
    int getCapacity() const {return capacity;}
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
    int size() const {
      return cache.size();
    }
    bool isFull() const {
      return size() == capacity;
    }
    bool contains(K key){
      return (map.find(key) != map.end());
    }
    void decCapacity(){
      if(capacity > 0){
	capacity -= 1;
      }
      assert(size() <= capacity);
    }
    void incCapacity(){
      capacity+=1;
    }
    int getCapacity() const {return capacity;}    
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
    std::pair<K,V> evict(){
      assert(cache.size());
      auto result = cache.back().second;
      map.erase(cache.back().first);      
      cache.pop_back();      
      return result;
    }
    std::pair<K,V> evict(K key){
      auto found = map.find(key);
      assert(found != map.end());
      auto result = *(found->second);
      map.erase(result.first);      
      cache.erase(found->second);      
      return result;
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
    lru<K,V> t1;
    lfu<K,V> t2;
    lru<K,int> b1, b2;
    arc(int cap) : capacity{cap},
		   t1{cap/2},
		   t2{cap-cap/2},
		   b1{cap/2},
		   b2{cap-cap/2}
    {
      
    }
    std::pair<K,V> evictT2(){
      auto evictedElement = t2.evict();
      if(b2.contains(evictedElement.first)) {
	b2.get(evictedElement.first);
      } else {
	b2.put(evictedElement.first, 0);
      }
      return evictedElement;
    }
    std::pair<K,V> evictT1(){
      auto evictedElement = t1.evict();
      if(b1.contains(evictedElement.first)) {
	  b1.get(evictedElement.first);
      } else {
	  b1.put(evictedElement.first, 0);
      }
      return evictedElement;
    }
    template<typename F>
    V get(K key, F functionToGet){
      if(t1.contains(key)){ //Found in T1, move it to T2
	auto element = t1.evict(key);
	if(t2.isFull()){
	  evictT2();	  
	}	
	t2.put(element.first, element.second);
	return element.second;
      } else if (t2.contains(key)){ //Found in T2
	return t2.get(key);
      }
      //Not found in T1 and T2
      if (b2.contains(key) && t1.size()) { 
	evictT1();
	t1.decCapacity();
	if(t2.getCapacity() < capacity){
	  t2.incCapacity();
	}
      } else if (b1.contains(key) && t2.size()) {
	evictT2();
	t2.decCapacity();
	if(t1.getCapacity() < capacity){
	  t1.incCapacity();
	}
      }
      auto val = functionToGet(key);
      if(t1.isFull()){
	evictT1();
      }
      t1.put(key, val);
      return val;
    }
    
    std::string toString(){
      std::stringstream ss;

      ss << "t1 size " << t1.size() << ":" << t1.toString();
      ss << "t2 size " << t2.size() << ":" << t2.toString();
      ss << "b1: " << b1.toString();
      ss << "b2: " << b2.toString();
      return ss.str();
    }
    
  };
}
