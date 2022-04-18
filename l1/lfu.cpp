#include <iostream>
#include "cache.hpp"
#include <string>


int slowGetCache(int k){
    return k;
}
int main (void) {

LfuCache<int, int> cache(5);

cache.findOrAdd(1, slowGetCache);

 
return 0;
}
