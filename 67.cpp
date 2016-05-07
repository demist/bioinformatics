#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

string reverse(string s)
{
    string res = "";
    for (int i = s.length() - 1; i >= 0; i--)
    {
        auto x = s[i];
        if (x == 'A')
            res += "T";
        if (x == 'T')
            res += "A";
        if (x == 'C')
            res += "G";
        if (x == 'G')
            res += "C";
    }
    return res;
}

unordered_map<string, vector<int>> kmers_dict(int k, string s)
{
    unordered_map<string, vector<int>> res;
    for (auto i = 0; i < s.length() - k + 1; i++)
    {
        auto kmer = s.substr(i, k);
        auto it = res.find(kmer);
        if (it == res.end())
        {
            res[kmer] = vector<int>();
            res[reverse(kmer)] = vector<int>();
        }
        res[kmer].push_back(i);
        res[reverse(kmer)].push_back(i);
    }
    return res;
}

void kmers()
{
    ifstream in("input.txt");
    int k;
    string s1, s2;
    in >> k >> s1 >> s2;
    in.close();
    vector<pair<int, int>> res;
    auto b = kmers_dict(k, s2);
    for (auto i = 0; i < s1.length() - k + 1; i++)
    {
        auto cur = s1.substr(i, k);
        auto it = b.find(cur);
        if (it != b.end())
        {
            for (auto x : it->second)
                res.push_back(make_pair(i, x));
        }
    }
    sort(res.begin(), res.end());
    ofstream out("output.txt");
    for (auto x : res)
        out << "(" << x.first << ", " << x.second << ")" << endl;
    out.close();
}

int main()
{
    kmers();
    return 0;
}