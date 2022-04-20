#include <unordered_map>
#include <list>
#include <algorithm>

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
std::list<typename std::unordered_map<K, DataItem>::iterator> itemsList;
//typename std::unordered_map<K, DataItem>::iterator smallestCountItemIt;
public:
LfuCache(int sz) : size{sz} { }

template <typename F>
V findOrAdd(K key, F addFunc) {
	auto hit = data.find(key);
	if(hit != data.end()) { //found in cache
        hit->second.counter++; 
		std::sort(itemsList.begin(), itemsList.end(), [](DataItem* i1, DataItem* i2)->bool{ return i1->counter < i2->counter; });
		return hit->second.value;
	} else { //not found in cache
		DataItem newItem;
		newItem.value = addFunc(key);
		newItem.key = key;
		newItem.count = 0;
		 
		
		if(data.size() == size){ 	//cache is full, need to erase least-frequently-used element
			data.erase(itemsList.rbegin());
			itemsList.erase(itemsList.rbegin());
		} 
		
		//have more space in cache, go for it
		std::pair<K,DataItem> pair(key, newItem);
		auto insertIt = data.insert(pair);
		itemsList.insert(insertIt);
		
		std::sort(itemsList.begin(), itemsList.end(), [](DataItem* i1, DataItem* i2)->bool{ return i1->counter < i2->counter; });
		return newItem.value;
	}
	
}

};
