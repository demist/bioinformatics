#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

int dist(vector<vector<int>> g1, vector<vector<int>> g2)
{
    unordered_multimap<int, int> gr;
    for (auto x : g1)
    {
        for (auto i = 0; i < x.size() - 1; i++)
        {
            gr.insert(make_pair(x[i], -1 * x[i + 1]));
            gr.insert(make_pair(-1 * x[i + 1], x[i]));
        }
        gr.insert(make_pair(x[x.size() - 1], -1 * x[0]));
        gr.insert(make_pair(-1 * x[0], x[x.size() - 1]));
    }
    for (auto x : g2)
    {
        for (auto i = 0; i < x.size() - 1; i++)
        {
            gr.insert(make_pair(x[i], -1 * x[i + 1]));
            gr.insert(make_pair(-1 * x[i + 1], x[i]));
        }
        gr.insert(make_pair(x[x.size() - 1], -1 * x[0]));
        gr.insert(make_pair(-1 * x[0], x[x.size() - 1]));
    }
    unordered_set<int> verts;
    for (auto x : gr)
    {
        if (verts.find(x.first) == verts.end())
            verts.insert(x.first);
    }
    auto comp = 0;
    while (!verts.empty())
    {
        comp++;
        queue<int> que;
        auto it = verts.begin();
        auto x = *it;
        verts.erase(it);
        que.push(x);
        while (!que.empty())
        {
            auto cur = que.front();
            que.pop();
            auto rng = gr.equal_range(cur);
            for (auto it = rng.first; it != rng.second; it++)
            {
                auto edge = *it;
                auto it2 = verts.find(edge.second);
                if (it2 != verts.end())
                {
                    que.push(*it2);
                    verts.erase(it2);
                }
            }
        }
    }
    auto sm = 0;
    for (auto x : g1)
        sm += x.size();
    return sm - comp;
}

int main()
{
    vector<vector<int>> g1, g2;
    char ctmp;
    int itmp;
    char lane[100000];
    ifstream in;
    in.open("input.txt");
    in.getline(lane, 100000);
    istringstream input(lane);
    vector<int> tmp;
    while (input >> ctmp)
    {
        if (ctmp == ')')
        {
            g1.push_back(tmp);
            tmp.clear();
            continue;
        }
        if (ctmp == '(')
            continue;
        input >> itmp;
        if (ctmp == '+')
            tmp.push_back(itmp);
        if (ctmp == '-')
            tmp.push_back(-1 * itmp);
    }
    in.getline(lane, 100000);
    istringstream input2(lane);
    while (input2 >> ctmp)
    {
        if (ctmp == ')')
        {
            g2.push_back(tmp);
            tmp.clear();
            continue;
        }
        if (ctmp == '(')
            continue;
        input2 >> itmp;
        if (ctmp == '+')
            tmp.push_back(itmp);
        if (ctmp == '-')
            tmp.push_back(-1 * itmp);
    }
    cout << dist(g1, g2) << endl;
    return 0;
}