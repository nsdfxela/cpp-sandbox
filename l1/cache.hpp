#include <map>


template <typename K, typename V>
class LfuCache {
public:

class FreqEntry {
public:
	//unique_ptr<K> key;
	int count = 0;
};


template <typename F>
V findOrAdd(K key, F addFunc) {
	return addFunc(key);
}

};
