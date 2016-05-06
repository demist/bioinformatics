#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

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
    unordered_map<int, int> tmp;
    for (auto x : base)
    {
        if (tmp.find(x) != tmp.end())
            tmp[x]++;
        else
            tmp[x] = 1;
    }
    auto result = 0;
    for (auto x : ch)
    {
        if (tmp.find(x) != tmp.end() && tmp[x] > 0)
        {
            result++;
            tmp[x]--;
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


void seq()
{
    vector<int> aminos;
    int n;
    vector<int> spec;
{
    ifstream in;
    in.open("input.txt");
    int m, tmp;
    in >> m >> n;
    while (in >> tmp)
        spec.push_back(tmp);
    in.close();
    map<int, int> dif;
    for (auto x : spec)
    {
        for (auto y : spec)
        {
            auto d = x - y;
            if (d > 0)
            {
                if (dif.find(d) != dif.end())
                    dif[d]++;
                else
                    dif[d] = 1;
            }
        }
    }
    multimap<int, int, greater<int>> revdif;
    for (auto x : dif)
    {
        if (x.first >= 57 && x.first <= 200)
            revdif.insert(make_pair(x.second, x.first));
    }
    set<int> amtmp;
    int count1 = 0;
    auto it = revdif.begin();
    auto pres = it->first;
    while(it != revdif.end() && (count1 < m || it->first == pres))
    {
        pres = it->first;
        amtmp.insert(it->second);
        count1 += 1;
        it++;
    }
    for (auto x : amtmp)
        aminos.push_back(x);
}
{
    list<vector<int>> leaderboard;
    auto leaderPeptide = vector<int>();
    leaderboard.push_back(leaderPeptide);
    auto pre_size = 0;
    auto cur_lead_score = 10000;
    bool flag = true;
    while (!leaderboard.empty() && flag)
    {
        //if (leaderboard.size() == pre_size)
        //    flag = false;
        pre_size = leaderboard.size();
        //cout << leaderboard.size() << endl;
        //expand
        //cout << "expand" << endl;
        {
            auto sz = leaderboard.size();
            auto it = leaderboard.begin();
            list<vector<int>> nl;
            //cout << "nl1:" << nl.size() << endl;
            for (auto i = 0; i < sz; i++)
            {
                for (auto x : aminos)
                {
                    auto c = *it;
                    c.push_back(x);
                    if (mass(c) <= spec[spec.size() - 1])
                        nl.push_back(c);
                }
                it++;
            }
            //cout << "nl2:" << nl.size() << endl;
            leaderboard.clear();
            leaderboard = nl;
        }
        {
            map<int, int> all;
            vector<vector<int>> tmpvec;
            for (auto x : leaderboard)
                tmpvec.push_back(x);
            for (auto i = 0; i < tmpvec.size(); i++)
            {
                auto cyclo = getCyclo(tmpvec[i]);
                auto sc = score(cyclo, spec);
                vector<int> test = {99,71,137,57,72,57};
                if (tmpvec[i] == test)
                {
                    auto c1 = getCyclo(leaderPeptide);
                    //cout << "here1 " << cur_lead_score << " " << mass(tmpvec[i]) << " " << sc << " " << score(c1, spec) << endl;
                }
                if (mass(tmpvec[i]) == spec[spec.size() - 1]  && sc < cur_lead_score)
                {
                    auto c1 = getCyclo(leaderPeptide);
                    //cout << "here2 " << cur_lead_score << " " << mass(tmpvec[i]) << " " << sc << " " << score(c1, spec) << endl;
                    cur_lead_score = sc;
                    leaderPeptide = tmpvec[i];
                }
                auto r = all.find(sc);
                if (r == all.end())
                    all[sc] = 1;
                else
                    all[sc]++;

            }
            unordered_set<int> good;
            auto it = all.begin();
            auto count = 0;
            while (count < n && it != all.end())
            {
                good.insert(it->first);
                count += it->second;
                it++;
            }
            //for (auto x : good)
            //    cout << x << " ";
            //cout << endl;
            //cout << good.size() << endl;
            //cout << good.size() << ":" << *(good.begin()) << endl;
            //cout << "making new leader board" << endl;
            list<vector<int>> newleaders;
            for (auto i = 0; i < tmpvec.size(); i++)
            {
                auto cyclo = getCyclo(tmpvec[i]);
                auto sc = score(cyclo, spec);
                {
                    if (good.find(sc) != good.end())
                        newleaders.push_back(tmpvec[i]);
                }
            }
            leaderboard = newleaders;
            //auto test = *leaderboard.begin();
            //for (auto x : test)
            //    cout << x << " ";
            //cout << endl;
        }
    }
    for (auto i = 0; i < leaderPeptide.size() - 1; i++)
        cout << leaderPeptide[i] << "-";
    cout << leaderPeptide[leaderPeptide.size() - 1] << endl;
}
}

int main()
{
    seq();
    return 0;
}