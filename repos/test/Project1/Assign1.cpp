#include <queue>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <functional>

using namespace std;

struct Key {
    Key(string _name, int _count) : name(_name), number_of_occur(_count) {}
    string name;
    int number_of_occur;
};

auto cmp = [](const Key* left, const Key* right)
{ if (left != NULL && right != NULL) return left->number_of_occur < right->number_of_occur;
else return true;
};

priority_queue<Key*, vector<Key*>, decltype(cmp)> pq(cmp);
unordered_map<string, Key*> keyMap;

void sendKey(int kn) {

    stringstream ss;
    ss << "key" << kn;
    string my_key = ss.str();

    if (keyMap.find(my_key) != keyMap.end())
    {
        keyMap[my_key]->number_of_occur++;
    }
    else {
        cout << my_key << endl;
        Key* newKey = new Key(my_key, 1);
        keyMap[my_key] = newKey;
        //pq.push(newKey);
        pq.emplace(newKey);
    }
}

void retriveTops(int n) {

    /*for (auto i = 0; i < n; i++)
    {
        cout << "Top " << pq.top()->name << "cnt " << pq.top()->number_of_occur << endl;
        pq.pop();
    }*/
    while (!pq.empty())
    {
        cout << "Top " << pq.top()->name << "cnt " << pq.top()->number_of_occur << endl;
        pq.pop();
    }
}
bool isTop()

int main()
{
    for (int i = 1; i <= 1000; i++)
    {
        if (i % 5) sendKey(5);
        if (i % 2) sendKey(2);
        if (i % 3) sendKey(3);
        if (i % 7) sendKey(7);        
        if (i % 13) sendKey(13);
        if (i % 17) sendKey(17);
        if (i % 11) sendKey(11);        
    }

    retriveTops(2);
}
