#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <set>
#include <sstream>

using namespace std;

set<int> or_weights = {57,71,87,97,99,101,103,113,114,115,128,129,131,137,147,156,163,186};

set<string> result;

vector<int> getCyclo(vector<int> peptide)
{
    multiset<int> res;
    res.insert(0);
    for (auto i = 1; i < peptide.size(); i++)
    {
        for (auto pos = 0; pos < peptide.size(); pos++)
        {
            auto tmp = 0;
            for (auto j = 0; j < i; j++)
            {
                if (pos + j < peptide.size())
                    tmp += peptide[pos + j];
                else
                    tmp += peptide[pos + j - peptide.size()];
            }
            res.insert(tmp);
        }
    }
    auto tmp = 0;
    for (auto x : peptide)
        tmp += x;
    res.insert(tmp);
    vector<int> ret;
    for (auto x : res)
        ret.push_back(x);
    return ret;
}

int getMass(vector<int> peptide)
{
    auto res = 0;
    for (auto x : peptide)
        res += x;
    return res;
}

bool check(vector<int> a, vector<int> b)
{
    if (a.size() != b.size())
        return false;
    for (auto i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return false;
    return true;
}

void getNext(int level, vector<int> in, vector<int> w, vector<int> cur, set<int> indexes)
{
    if (indexes.empty())
    {
        auto ch = getCyclo(cur);
        if (check(ch, in))
        {
            ostringstream tmp;
            for (auto i = 0; i < cur.size() - 1; i++)
                tmp << cur[i] << "-";
            tmp << cur[cur.size() - 1];
            result.insert(tmp.str());
        }
    }
    for (auto x : indexes)
    {
        //cout << level << ":" << x << endl;
        auto newone = cur;
        auto newind = indexes;
        newone.push_back(w[x]);
        newind.erase(x);
        getNext(level + 1, in, w, newone, newind); 
    }
}

void recons()
{
    ifstream in;
    in.open("input.txt");
    int tmp;
    vector<int> input;
    while (in >> tmp)
        input.push_back(tmp);
    in.close();
    auto psize = 1;
    while (true)
    {
        if ((psize - 1) * psize + 2 == input.size())
            break;
        psize++;
    }
    vector<int> weights;
    for (auto i = 1; i <= psize; i++)
            weights.push_back(input[i]);
    cout << psize << " " << weights.size() << endl;
    set<int> indexes;
    for (auto i = 0; i < psize; i++)
        indexes.insert(i);
    vector<int> cur;
    getNext(0, input, weights, cur, indexes);
    for (auto x : result)
        cout << x << " ";
    cout << endl;
}

int main()
{
    recons();
    cout << endl;
    return 0;
}