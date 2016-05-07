#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

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

vector<pair<int, int>> two_breakGr(vector<pair<int, int>> edges, int i, int j, int k, int l)
{
    unordered_map<int, int> bad;
    bad.insert(make_pair(i, j));
    bad.insert(make_pair(j, i));
    bad.insert(make_pair(k, l));
    bad.insert(make_pair(l, k));
    vector<pair<int, int>> res;
    for (auto x : edges)
        if (bad.find(x.first) == bad.end() || bad[x.first] != x.second)
            res.push_back(x);
    res.push_back(make_pair(i, k));
    res.push_back(make_pair(j, l));
    
    return res;
}

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

void two_break_on_genome()
{
    ifstream in("input.txt");
    char ctmp;
    int itmp;
    vector<vector<int>> genome; 
    vector<int> tmp;
    while (in >> ctmp)
    {
        if (ctmp == '(')
            continue;
        if (ctmp == ')')
        {
            genome.push_back(tmp);
            tmp.clear();
            continue;
        }
        in >> itmp;
        if (ctmp == '+')
            tmp.push_back(itmp);
        if (ctmp == '-')
            tmp.push_back(-1 * itmp);
    }
    in.close();
    int i, j, k, l;
    cin >> i >> j >> k >> l;
    auto g1 = colored(genome);
    auto g2 = two_breakGr(g1, i, j, k, l);
    auto res = gr2g(g2);
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
}

int main()
{
    two_break_on_genome();
    return 0;
}