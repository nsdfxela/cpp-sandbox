#include <iostream>
#include "cache.hpp"
#include <string>


int slowGetCache(int k){
    return k;
}
int main (void) {

LfuCache<int, int> cache(3);

cache.findOrAdd(1, slowGetCache);
cache.findOrAdd(1, slowGetCache);
cache.findOrAdd(1, slowGetCache);

cache.findOrAdd(2, slowGetCache);
cache.findOrAdd(2, slowGetCache);

cache.findOrAdd(3, slowGetCache);

cache.findOrAdd(5, slowGetCache);
cache.findOrAdd(6, slowGetCache);

cache.findOrAdd(2, slowGetCache);
cache.findOrAdd(1, slowGetCache);
return 0;
}
