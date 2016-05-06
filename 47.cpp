#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>

using namespace std;

int mass(char c)
{
  if (c == 'G')
    return 57;
  if (c == 'A')
    return 71;
  if (c == 'S')
    return 87;
  if (c == 'P')
    return 97;
  if (c == 'V')
    return 99;
  if (c == 'T')
    return 101;
  if (c == 'C')
    return 103;
  if (c == 'I')
    return 113;
  if (c == 'L')
    return 113;
  if (c == 'N')
    return 114;
  if (c == 'D')
    return 115;
  if (c == 'K')
    return 128;
  if (c == 'Q')
    return 128;
  if (c == 'E')
    return 129;
  if (c == 'M')
    return 131;
  if (c == 'H')
    return 137;
  if (c == 'F')
    return 147;
  if (c == 'R')
    return 156;
  if (c == 'Y')
    return 163;
  if (c == 'W')
    return 186;
  return 0;
}

int getPepMass(string a)
{
    auto result = 0;
    for (auto x : a)
        result += mass(x);
    return result;
}

vector<int> spec(string in)
{
    vector<int> prefs(in.size() + 1);
    for (auto i = 0; i <= in.size(); i++)
    {
      auto tmp = in.substr(0, i);
      prefs[i] = getPepMass(tmp);
    }
    multiset<int> difs;
    for (auto i = 0; i < prefs.size(); i++)
        for (auto j = i + 1; j < prefs.size(); j++)
            difs.insert(prefs[j] - prefs[i]);
    vector<int> res;
    res.push_back(0);
    for (auto x : difs)
        res.push_back(x);
    return res;
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
    return result;
}

vector<string> getTop(vector<string> cur, vector<int> base, int n)
{
    map<int, int, greater<int>> scores;
    for (auto x : cur)
    {
        auto sp = spec(x);
        auto sc = score(sp, base);
        if (scores.find(sc) == scores.end())
            scores[sc] = 1;
        else
            scores[sc]++;
    }
    auto cnt = 1;
    auto it = scores.begin();
    set<int> good;
    while (cnt <= n && it != scores.end())
    {
        good.insert(it->first);
        cnt += it->second;
        it++;
    }
    vector<string> res;
    for (auto x : cur)
    {
        auto sp = spec(x);
        auto sc = score(sp, base);
        if (good.find(sc) != good.end())
            res.push_back(x);
    }
    return res;
}

int main()
{
    ifstream in;
    in.open("input.txt");
    int n;
    vector<string> lead;
    in >> n;
    string tmp;
    while (in >> tmp)
        lead.push_back(tmp);
    in.close();
    in.open("input1.txt");
    vector<int> base;
    int t;
    while (in >> t)
        base.push_back(t);
    auto res = getTop(lead, base, n);
    for (auto x : res)
        cout << x << " ";
    cout << endl;
    return 0;
}