#include<bits/stdc++.h>
#include <map>
#include <unordered_map>
#include <mutex>
#include <thread>
using namespace std;

class LRUCache {
    list<pair<int,int>> data;
    unordered_map<int,list<pair<int,int>>::iterator> m;
    int capacity;
    mutex m_mutex;
public:
    LRUCache(int _capacity) : capacity(_capacity) {
        
    }
    
    int get(int key) {
        lock_guard<mutex> lk(m_mutex);
        if (!m.count(key)) {
            return -1;
        }
        int ret = m[key]->second;
        data.splice(data.begin(), data, m[key]);
        m[key] = data.begin();
        return ret; 
    }
    
    void put(int key, int value) {
        lock_guard<mutex> lk(m_mutex);
        if (m.count(key)) {
            data.splice(data.begin(),data,m[key]);
            data.begin()->second = value;
        } else {
            if (m.size() == capacity) {
                int rev_key = data.back().first;
                data.pop_back();
                m.erase(rev_key);
            }
            data.emplace_front(key, value);
            
        }
        m[key] = data.begin();
    }
};

int main()
{
    LRUCache lc(10);
    thread writer1([&]{lc.put(0, 1);});
    thread writer2([&]{lc.put(0, 2);});
    thread reader1([&]{lc.get(0);});
    writer1.join();
    writer2.join();
    reader1.join();
}