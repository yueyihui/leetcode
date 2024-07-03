#include <bits/stdc++.h>
using namespace std;

// https://www.naukri.com/code360/problems/lru-cache-implementation_670276
class LRUCache
{
  private:
    list<int> time;
    unordered_map<int, pair<int, list<int>::iterator>> map;
    int capacity;

  public:
    LRUCache(int capacity) { this->capacity = capacity; }

    int get(int key)
    {
        auto it = map.find(key);
        if (it == map.end())
            return -1;
        else
        {
            time.erase(it->second.second);
            time.push_front(key);
            it->second.second = time.begin();
            return it->second.first;
        }
    }

    void put(int key, int value)
    {
        auto it = map.find(key);
        if (it != map.end())
        {
            time.erase(it->second.second);
            time.push_front(key);
            it->second = {value, time.begin()};
            return;
        }
        if (map.size() == capacity)
        {
            int oldest = time.back();
            time.pop_back();
            map.erase(oldest);
        }
        time.push_front(key);
        map.insert({key, {value, time.begin()}});
    }
};
