#include <iostream>
#include <fstream>
#include <map>
#include <list>

using namespace std;

void dfs(map<int, list<pair<int, int>>> gr, int source, int sink, int cur, int weight, list<int> path, map<int, list<int>, std::greater<int>>& paths)
{
    if (cur == sink && path.size() != 1)
    {
        paths[weight] = path;
        return;
    }
    for (auto x : gr[cur])
    {
        auto next_v = x.first;
        auto next_w = x.second;
        auto p = path;
        p.push_back(next_v);
        dfs(gr, source, sink, next_v, weight + next_w, p, paths);
    }
}

void longest()
{
    ifstream in;
    in.open("input.txt");
    int source, sink;
    in >> source >> sink;
    int v1, v2, w;
    map<int, list<pair<int, int>>> gr;
    while (in >> v1 >> v2 >> w)
        gr[v1].push_back(make_pair(v2, w));
    auto cur = source;
    auto weight = 0;
    list<int> path;
    path.push_back(source);
    map<int, list<int>, std::greater<int>> paths;
    dfs(gr, source, sink, cur, weight, path, paths);
    if (!paths.empty())
    {
        auto it = paths.begin();
        cout << it->first << endl;
        auto sz = it->second.size();
        auto it2 = it->second.begin();
        for (auto i = 0; i < sz; i++)
        {
            cout << *it2;
            if (i != sz - 1)
                cout << "->";
            else
                cout << endl;
            it2++;
        }
    }
}

int main()
{
    longest();
    return 0;
}