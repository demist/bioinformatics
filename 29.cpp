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
    map<int, int> indeg;
    int u1, u2;
    char lane[256];
    while (in.getline(lane, 256))
    {
        istringstream tmp(lane);
        tmp >> u1;
        while (tmp >> u2)
        {
            gr[u1].insert(u2);
            auto it = indeg.find(u2);
            if (it == indeg.end())
                indeg[u2] = 1;
            else 
                indeg[u2]++;
            if (gr.find(u2) == gr.end())
                gr[u2] = set<int>();
            //cout << u1 << " " << u2 << endl;
        }
    }
    in.close();
    list<int> res;
    int v1, v2;
    for (auto x : gr)
    {
        auto it = indeg.find(x.first);
        auto indegval = 0;
        if (it != indeg.end())
            indegval = indeg[x.first];
        if (x.second.size() - indegval == 1)
            v1 = x.first;
        if (x.second.size() - indegval == -1)
            v2 = x.first;
    }
    gr[v2].insert(v1);
    stack<int> st;
    st.push(v1);
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
    bool flag = false;
    auto it = res.end();
    it--;
    it--;
    while (true)
    {
        if (*it == v2)
        {
            if (flag)
            {
                cout << v2 << endl;
                break;
            }
            else
                flag = true;
        }
        else
            if (flag)
                cout << *it << "->";
        if (it == res.begin())
        {
            it = res.end();
            it--;
        }
        it--;
    }
}

int main()
{
    eulerian();
    return 0;
}