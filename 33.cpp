#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <sstream>

using namespace std;

void contig()
{
    ifstream in;
    in.open("input.txt");
    vector<string> kmers;
    string tmp;
    map<int, multiset<int>> debr;
    map<int, string> mapper;
    map<string, int> rev_mapper;
    auto cnt = 0;
    map<int, int> indegree;
    while (in >> tmp)
    {
        kmers.push_back(tmp);
        auto pre =  tmp.substr(0, tmp.length() - 1);
        auto suf = tmp.substr(1, tmp.length() - 1);
        auto it = rev_mapper.find(pre);
        if (it == rev_mapper.end())
        {
            rev_mapper[pre] = cnt + 1;
            mapper[cnt + 1] = pre;
        }
        it = rev_mapper.find(suf);
        if (it == rev_mapper.end())
        {
            rev_mapper[suf] = cnt + 2;
            mapper[cnt + 2] = suf;
        }
        cnt += 2;
        debr[rev_mapper[pre]].insert(rev_mapper[suf]);
        auto it2 = indegree.find(rev_mapper[suf]);
        if (it2 == indegree.end())
            indegree[rev_mapper[suf]] = 1;
        else
            indegree[rev_mapper[suf]]++;
    }
    in.close();
    list<list<int>> contigs;
 /*   for (auto x : debr)
    {
        if (indegree[x.first] == 1 && x.second.size() == 1)
            continue;
        for (auto y : x.second)
        {
            list<int> res;
            res.push_back(x.first);
            res.push_back(y);
            auto u = y;
            if (debr[u].size() == 1 && indegree[u] == 1)
            {
                u = *(debr[u].begin());
                res.push_back(u);
            }
            if (!res.empty())
                contigs.push_back(res);
        }
    }
*/
    for (auto x : debr)
    {
        if (indegree[x.first] == 1 && x.second.size() == 1)
            continue;
        auto node = x.first;
        for (auto next : debr[x.first])
        {
            list<int> res;
            res.push_back(node);
            res.push_back(next);
            while (debr[next].size() == 1 && indegree[next] == 1)
            {
                node = next;
                next = *(debr[node].begin());
                res.push_back(next);
            }
            if (!res.empty())
                contigs.push_back(res);
        }
    }
    list<string> results;
    for (auto x : contigs)
    {
        ostringstream out;
        auto it = x.begin();
        out << mapper[*it];
        it++;
        while (it != x.end())
        {
            out << mapper[*it][mapper[*it].length() - 1];
            it++;
        }
        results.push_back(out.str());
    }
    ofstream ans;
    ans.open("output.txt");
    for (auto x : results)
    {
        bool flag = true;
        for (auto y : results)
        {
            if (y.length() > x.length() && y.substr(y.length() - x.length(), x.length()) == x)
                flag = false;
        }
        if (flag)
            ans << x << endl;
    }
    ans.close();
}

int main()
{
    contig();
    return 0;
}