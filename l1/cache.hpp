#include <unordered_map>


template <typename K, typename V>
class LfuCache {
public:
struct DataItem {
	V value;
	int counter = 0;
};
private:
std::unordered_map<K, DataItem> data;
int size = 0;
typename std::unordered_map<K, DataItem>::iterator smallestCountItemIt;
public:
LfuCache(int sz) : size{sz} { }

template <typename F>
V findOrAdd(K key, F addFunc) {
	auto hit = data.find(key);
	if(hit != data.end()) { //found in cache
        hit->second.counter++; 
		if(smallestCountItemIt == data.end() || hit->second.counter > smallestCountItemIt->counter ){
			smallestCountItemIt = hit;
		}
		
		return hit->second.value;
	} else { //not found in cache
		if(data.size() == size){ //cache is full, need to erase least-frequently-used element

		} else { //have more space in cache, go for it
			
		}
		
	}
	return addFunc(key);
}

};
