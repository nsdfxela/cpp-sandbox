#include <unordered_map>
#include <list>
#include <algorithm>
#include <iostream>

template <typename K, typename V>
class LfuCache {
public: 
struct DataItem {
	K key;
	V value;
	int counter = 0;
};
private:
std::unordered_map<K, DataItem> data;
int size = 0;

//typename std::unordered_map<K, DataItem>::iterator smallestCountItemIt;
public:
LfuCache(int sz) : size{sz} { }
std::list<DataItem*> itemsList;
template <typename F>
V findOrAdd(K key, F addFunc) {
	auto hit = data.find(key);
	if(hit != data.end()) { //found in cache
        hit->second.counter++; 
		itemsList.sort([](DataItem* i1, DataItem* i2) { return  i1->counter < i2->counter; });
	 
		std::cout << "hit \n";
		return hit->second.value;
	} else { //not found in cache
		DataItem newItem;
		newItem.value = addFunc(key);
		newItem.key = key;
		newItem.counter = 0;
		 
		
		if(data.size() == size){ 	//cache is full, need to erase least-frequently-used element
			std::cout << "cache is full \n";
			
			data.erase(itemsList.back()->key);
			itemsList.pop_back();
		} 
		
		//have more space in cache, go for it
		std::pair<K,DataItem> pair(key, newItem);
		auto insertIt = data.insert(pair);
		//itemsList.insert(&(*insertIt));
		
		itemsList.sort([](DataItem* i1, DataItem* i2) { return  i1->counter < i2->counter; });
		std::cout << "miss \n";	
		return newItem.value;
	}
	
}

};
