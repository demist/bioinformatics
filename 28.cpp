#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <stack>
#include <map>
#include <set>

using namespace std;

void eulerian()
{
    ifstream in;
    in.open("input.txt");
    map<int, set<int>> gr;
    int u1, u2;
    char lane[256];
    while (in.getline(lane, 256))
    {
        istringstream tmp(lane);
        tmp >> u1;
        while (tmp >> u2)
            gr[u1].insert(u2);
    }
    in.close();
    list<int> res;
    int v;
    for (auto x : gr)
    {
        if (x.second.size() % 2 == 1)
        {
            v = x.first;
            break;
        }
    }
    stack<int> st;
    st.push(v);
    while (!st.empty())
    {
        auto w = st.top();
        for (auto u : gr)
        {
            auto it = gr[w].find(u.first);
            if (it != gr[w].end())
            {
                st.push(u.first);
                gr[w].erase(it);
                break;
            }
        }
        if (w == st.top())
        {
            st.pop();
            res.push_back(w);
        }
    }
    auto cnt = 0;
    auto it = res.end();
    it--;
    while (it != res.begin())
    {
        cout << *it << "->";
        it--;
    }
    cout << *it << endl;
}

int main()
{
    eulerian();
    return 0;
}