#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>

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

vector<vector<int>> two_break_on_genome(vector<vector<int>> genome, int i, int j, int k, int l)
{
    auto g1 = colored(genome);
    auto g2 = two_breakGr(g1, i, j, k, l);
    auto res = gr2g(g2);
    return res;
}

vector<vector<int>> colored_cycles(vector<pair<int, int>> blue, vector<pair<int, int>> red)
{
    vector<vector<int>> cycles;
    auto size = blue.size() + red.size();
    vector<vector<int>> adj(size, vector<int>(2, 0));
    vector<bool> visited(size, false);
    for (auto e : blue)
    {
        adj[e.first - 1][0] = e.second - 1;
        adj[e.second - 1][0] = e.first - 1;
    }
    for (auto e : red)
    {
        adj[e.first - 1][1] = e.second - 1;
        adj[e.second - 1][1] = e.first - 1;
    }
    for (auto node = 0; node < size; node++)
    {
        if (!visited[node])
        {
            visited[node] = true;
            auto head = node;
            vector<int> cycle;
            cycle.push_back(head + 1);
            auto color = 0;
            while (true)
            {
                node = adj[node][color];
                if (node == head)
                {
                    cycles.push_back(cycle);
                    break;
                }
                cycle.push_back(node + 1);
                visited[node] = true;
                color = (color + 1) % 2;
            }
        }
    }
    return cycles;
}

void sorting()
{
    ifstream in("input.txt");
    vector<vector<int>> g1, g2;
    char lane[100000];
    in.getline(lane, 100000);
    vector<int> tmp;
    char ctmp;
    int itmp;
    istringstream in1(lane);
    while (in1 >> ctmp)
    {
        if (ctmp == '(')
            continue;
        if (ctmp == ')')
        {
            g1.push_back(tmp);
            tmp.clear();
            continue;
        }
        in1 >> itmp;
        if (ctmp == '+')
            tmp.push_back(itmp);
        if (ctmp == '-')
            tmp.push_back(-1 * itmp);
    }
    in.getline(lane, 100000);
    istringstream in2(lane);
    while (in2 >> ctmp)
    {
        if (ctmp == '(')
            continue;
        if (ctmp == ')')
        {
            g2.push_back(tmp);
            tmp.clear();
            continue;
        }
        in2 >> itmp;
        if (ctmp == '+')
            tmp.push_back(itmp);
        if (ctmp == '-')
            tmp.push_back(-1 * itmp);
    }
    in.close();
    auto red = colored(g2);
    vector<vector<vector<int>>> path;
    path.push_back(g1);
    while (dist(g1, g2) > 0)
    {
        auto cycles = colored_cycles(colored(g1), red);
        for (auto c : cycles)
        {
            if (c.size() > 3)
            {
                g1 = two_break_on_genome(g1, c[0], c[1], c[3], c[2]);
                path.push_back(g1);
                break;
            }
        }
    }
    for (auto x : path)
    {
        for (auto g : x)
        {
            cout << "(";
            for (auto i = 0; i < g.size(); i++)
            {
                cout << (g[i] > 0 ? "+" : "") << g[i];
                if (i != g.size() - 1)
                    cout << " ";
            }
            cout << ")";
        }
        cout << endl;
    }    
}

int main()
{
    sorting();
    return 0;
}