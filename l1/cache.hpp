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
int smallestCount = -1;
public:
LfuCache(int sz) : size{sz} {}

template <typename F>
V findOrAdd(K key, F addFunc) {
	auto hit = data.find(key);
	if(hit!=data.end()) {
                
		return hit->second.V;
	}
	return addFunc(key);
}

};
