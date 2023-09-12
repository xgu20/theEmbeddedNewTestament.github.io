#include <iostream>
#include <fstream>
#include <vector>
#include <priority_queue>
using namespace std;

int k = 100;
vector<ifstream> ifsVec;


for (int i = 0; i < k; ++i)
{
    ifstream ifs;
    ifs.open("text.txt")
    if (!ifs.is_open())
    {
        return -1;
    }
    ifsVec.push_back(ifs);
}
auto comp = [](auto& a, auto& b) {
    return a.second > b.second;
};
priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(comp)> pq(comp);
vector<int> res;
string buf;
int num;
for (int i = 0; i < k; ++i) {
    if (getline(buf, ifsvec[i])){
        num = stoi(buf);
        pq.push({i,num});
    }
}

while (!pq.empty()) {
    auto& p = pq.top();pq.pop();
    if (getline(buf, ifsvec[p.first])){
        num = stoi(buf);
        res.push_back(num);
        pq.push({p.first, num});
    }
}

