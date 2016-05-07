#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> ch2c(vector<int>& g)
{
    vector<int> result;
    for (auto i = 0; i < g.size(); i++)
    {
        if (g[i] > 0)
        {
            result.push_back(2 * g[i] - 1);
            result.push_back(2 * g[i]);
        }
        else
        {
            result.push_back(-2 * g[i]);
            result.push_back(-2 * g[i] - 1);
        }
    }

    return result;
}


vector<pair<int, int>> colored(vector<vector<int>> g)
{
    vector<pair<int, int>> edges;
    for (auto x : g)
    {
        auto s = ch2c(x);
        for (auto j = 0; j < s.size() / 2; j++)
        {
            auto head = 1 + 2 * j;
            auto tail = (2 + 2 * j) % s.size();
            edges.push_back(make_pair(s[head], s[tail]));
        }
    }
    
    return edges;
}

int main()
{
    ifstream in("input.txt");
    vector<vector<int>> g;
    vector<int> tmp;
    char ctmp;
    int itmp;
    while (in >> ctmp)
    {
        if (ctmp == '(')
            continue;
        if (ctmp == ')')
        {
            g.push_back(tmp);
            tmp.clear();
            continue;
        }
        in >> itmp;
        if (ctmp == '+')
            tmp.push_back(itmp);
        if (ctmp == '-')
            tmp.push_back(-1 * itmp);
    }

    auto res = colored(g);
    
    for (auto i = 0; i < res.size(); i++)
    {
        cout << "(" << res[i].first << ", " << res[i].second << ")";
        if (i != res.size() - 1)
            cout << ", ";
    }
    cout << endl;
    
    return 0;
}