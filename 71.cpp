#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<vector<int>> gr2g(vector<pair<int, int>> edges)
{
    vector<vector<int>> res;
    unordered_set<int> visit;
    vector<int> adj(2 * edges.size(), 0);
    for (auto x : edges)
    {
        adj[x.first - 1] = x.second - 1;
        adj[x.second - 1] = x.first - 1;        
    }
    for (auto x : edges)
    {
        auto orig = x.first;
        auto it = visit.find(orig);
        if (it != visit.end())
            continue;
        visit.insert(orig);
        int closing;
        if (orig % 2 == 0)
            closing = orig - 1;
        else
            closing = orig + 1;
        vector<int> p;
        auto i = 0;
        while (true)
        {
            if (orig % 2 == 0)
                p.push_back(orig / 2);
            else
                p.push_back(-1 * (orig + 1) / 2);
            auto dest = adj[orig - 1] + 1;
            i += 1;
            visit.insert(dest);
            if (dest == closing)
            {
                res.push_back(p);
                break;
            }
            if (dest % 2 == 0)
                orig = dest - 1;
            else
                orig = dest + 1;
            visit.insert(orig);
        }    
    }
    return res;
}

int main()
{
    ifstream in("input.txt");
    vector<pair<int, int>> edges;
    int v1, v2;
    while (in >> v1 >> v2)
        edges.push_back(make_pair(v1, v2));
    auto res = gr2g(edges);
    for (auto x : res)
    {
        cout << "(";
        for (auto i = 0; i < x.size(); i++)
        {
            cout << (x[i] > 0 ? "+" : "") << x[i];
            if (i != x.size() - 1)
                cout << " ";
        }
        cout << ")";
    }
    cout << endl;
    return 0;
}