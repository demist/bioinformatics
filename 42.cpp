#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <queue>
#include <map>
#include <omp.h>

using namespace std;

set<int> am = {57,71,87,97,99,101,103,113,114,115,128,129,131,137,147,156,163,186};

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
    if (tmp != 0)
        res.insert(tmp);
    vector<int> ret;
    for (auto x : res)
        ret.push_back(x);
    return ret;
}

int score(vector<int> ch, vector<int> base)
{
    multiset<int> tmp;
    for (auto x : base)
        tmp.insert(x);
    auto result = 0;
    for (auto x : ch)
    {
        auto it = tmp.find(x);
        if (it != tmp.end())
        {
            result++;
            tmp.erase(x);
        }
    }
    return 10000 - result;
}

int mass(vector<int> ch)
{
    auto result = 0;
    for (auto x : ch)
        result += x;
    return result;
}

void simil()
{
    ifstream in;
    in.open("input.txt");
    int n, tmp;
    in >> n;
    vector<int> spec;
    while (in >> tmp)
        spec.push_back(tmp);
    in.close();
    //cout << n << " " << spec.size() << endl;
    list<vector<int>> leaderboard;
    auto leaderPeptide = vector<int>();
    leaderboard.push_back(leaderPeptide);
    auto flag = true;
    auto pre_size = 0;
    auto cur_lead_score = 10000;
    while (!leaderboard.empty() && flag)
    {
        if (leaderboard.size() == pre_size)
            flag = false;
        pre_size = leaderboard.size();
        //cout << leaderboard.size() << endl;
        //expand
        //cout << "expand" << endl;
        {
            auto sz = leaderboard.size();
            auto it = leaderboard.begin();
            for (auto i = 0; i < sz; i++)
            {
                for (auto x : am)
                {
                    auto c = *it;
                    c.push_back(x);
                    leaderboard.push_back(c);
                }
                it++;
            }
        }
        {
            map<int, int> all;
            vector<vector<int>> tmpvec;
            for (auto x : leaderboard)
                tmpvec.push_back(x);
#pragma omp parallel for num_threads(4)
            for (auto i = 0; i < tmpvec.size(); i++)
            {
                auto cyclo = getCyclo(tmpvec[i]);
                auto sc = score(cyclo, spec);
#pragma omp critical
                {
                    if (sc < cur_lead_score)
                    {
                        cur_lead_score = sc;
                        leaderPeptide = tmpvec[i];
                    }
                    auto r = all.find(sc);
                    if (r == all.end())
                        all[sc] = 1;
                    else
                        all[sc]++;
                }
            }
            set<int> good;
            auto it = all.begin();
            auto count = 0;
            while (count < n && it != all.end())
            {
                good.insert(it->first);
                count += it->second;
                it++;
            }
            //cout << "making new leader board" << endl;
            list<vector<int>> newleaders;
#pragma omp parallel for num_threads(4)
            for (auto i = 0; i < tmpvec.size(); i++)
            {
                auto cyclo = getCyclo(tmpvec[i]);
                auto sc = score(cyclo, spec);
#pragma omp critical
                {
                    if (good.find(sc) != good.end())
                        newleaders.push_back(tmpvec[i]);
                }
            }
            leaderboard = newleaders;
        }
    }
    for (auto i = 0; i < leaderPeptide.size() - 1; i++)
        cout << leaderPeptide[i] << "-";
    cout << leaderPeptide[leaderPeptide.size() - 1] << endl;
}

int main()
{
    simil();
    return 0;
}