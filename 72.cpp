#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

void two_breakGr()
{
    ifstream in("input.txt");
    vector<pair<int, int>> edges;
    int v1, v2;
    while (in >> v1 >> v2)
        edges.push_back(make_pair(v1, v2));
    in.close();
    int i, j, k, l;
    cin >> i >> j >> k >> l;
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
    for (auto i = 0; i < res.size(); i++)
    {
        cout << "(" << res[i].first << ", " << res[i].second << ")";
        if (i != res.size() - 1)
            cout << ", ";
    }
    cout << endl;
}

int main()
{
    two_breakGr();
    return 0;
}