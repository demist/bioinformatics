#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <stack>
#include <list>
#include <vector>

using namespace std;



void reconst()
{
    ifstream in;
    in.open("input.txt");
    int k, d;
    in >> k >> d;
    string tmp1, tmp2;
    multimap<string, string> begs;
    multimap<string, string> ends;
    multimap<string, string> graph;
    while (in >> tmp1 >> tmp2)
    {
        auto pre = tmp1.substr(0, k - 1) + tmp2.substr(0, k - 1);
        auto suf = tmp1.substr(1, k - 1) + tmp2.substr(1, k - 1);
        begs.insert(make_pair(pre, tmp1 + tmp2));
        ends.insert(make_pair(suf, tmp1 + tmp2));
    }
    map<string, int> deg;
    in.close();
    for (auto x : ends)
    {
        auto it = begs.find(x.first);
        if (it != begs.end())
            graph.insert(make_pair(x.second, it->second));
        auto it2 = deg.find(x.second);
        if (it2 == deg.end())
            deg[x.second] = 1;
        else
            deg[x.second]++;
        auto it3 = deg.find(it->second);
        if (it3 == deg.end())
            deg[it->second] = -1;
        else
            deg[it->second]--;
    }
    stack<string> st;
    for (auto x : deg)
    {
        if (x.second % 2 == 1)
        {
            st.push(x.first);
            break;
        }
    }
    list<string> res;
    while (!st.empty())
    {
        auto v = st.top();
        auto it = graph.find(v);
        if (it == graph.end())
        {
            res.push_front(v);
            st.pop();
        }
        else
        {
            st.push(it->second);
            graph.erase(it);
        }
    }
    string result(2 * k + d + begs.size() - 1, 'A');
    auto cnt = 0;
    for (auto x : res)
    {
        for (auto j = 0; j < k; j++)
            result[cnt + j] = x[j];
        for (auto j = 0; j < k; j++)
            result[cnt + k + d + j] = x[k + j];
        cnt++;
    }
    ofstream out;
    out.open("output.txt");
    out << result << endl;
    out.close();
}

int main()
{
    reconst();
    return 0;
}