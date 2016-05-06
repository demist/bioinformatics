#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string addIndel(string a, int pos)
{
    return a.substr(0, pos + 1) + "-" + a.substr(pos + 1);
}

void fitting()
{
    ifstream in;
    in.open("input.txt");
    string s1, s2;
    in >> s1 >> s2;
    in.close();
    vector<vector<int>> d(s1.length() + 1, vector<int>(s2.length() + 1, 0));
    for (auto i = 1; i < s1.length() + 1; i++)
    {
        for (auto j = 1; j < s2.length() + 1; j++)
        {
            auto x1 = d[i - 1][j] - 1;
            auto x2 = d[i][j - 1] - 1;
            auto m = s1[i - 1] == s2[j - 1] ? 1 : -1;
            auto x3 = d[i - 1][j - 1] + m;
            if (x1 >= x2 && x1 >= x3)
            {
                d[i][j] = x1;
                continue;
            }
            if (x2 >= x1 && x2 >= x3)
            {
                d[i][j] = x2;
                continue;
            }
            if (x3 >= x1 && x3 >= x2)
            {
                d[i][j] = x3;
                continue;
            }
        }
    }
    auto best = 0;
    auto b_i = 0, b_j = 0;
    for (auto i = 0; i < s1.length() + 1; i++)
    {
        if (d[i][d[0].size() - 1] >= best)
        {
            best = d[i][d[0].size() - 1];
            b_i = i;
            b_j = d[0].size() - 1;
        }
    }
    ofstream out;
    out.open("output.txt");
    out << best << endl;
    string res1 = s1.substr(0, b_i), res2 = s2.substr(0, b_j);
    while (b_i >= 1 && b_j >= 1)
    {
        auto x1 = d[b_i - 1][b_j - 1] + (s1[b_i - 1] == s2[b_j - 1] ? 1 : -1);
        auto x2 = d[b_i - 1][b_j] - 1;
        auto x3 = d[b_i][b_j - 1] - 1;
        auto x4 = 0;
        if (d[b_i][b_j] == x1)
        {
            b_i -= 1;
            b_j -= 1;
            continue;
        }
        if(d[b_i][b_j] == x2)
        {
            res2 = addIndel(res2, b_j - 1);
            b_i -= 1;
            continue;
        }
        if (d[b_i][b_j] == x3)
        {
            res1 = addIndel(res1, b_i - 1);
            b_j -= 1;
            continue;
        }
    }
    out << res1.substr(b_i) << endl;
    out << res2;
    out.close();
}

int main()
{
    fitting();
    return 0;
}