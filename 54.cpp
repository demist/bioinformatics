#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int getId(char a)
{
     if (a == 'A')
         return 0;
     if (a == 'C')
         return 1;
     if (a == 'D')
         return 2;
     if (a == 'E')
         return 3;
     if (a == 'F')
         return 4;
     if (a == 'G')
         return 5;
     if (a == 'H')
         return 6;
     if (a == 'I')
         return 7;
     if (a == 'K')
         return 8;
     if (a == 'L')
         return 9;
     if (a == 'M')
         return 10;
     if (a == 'N')
         return 11;
     if (a == 'P')
         return 12;
     if (a == 'Q')
         return 13;
     if (a == 'R')
         return 14;
     if (a == 'S')
         return 15;
     if (a == 'T')
         return 16;
     if (a == 'V')
         return 17;
     if (a == 'W')
         return 18;
     if (a == 'Y')
         return 19;
     return -1;
}

void local_score()
{
    ifstream in;
    in.open("input.txt");
    string s1, s2;
    in >> s1 >> s2;
    in.close();
    vector<vector<int>> matrix(20, vector<int>(20));
    in.open("matrix.txt");
    int tmp;
    for (auto i = 0; i < 20; i++)
    {
        for (auto j = 0; j < 20; j++)
        {
            in >> tmp;
            matrix[i][j] = tmp;
        }
    }
    in.close();
    auto gap = -5;
    vector<vector<int>> d(s1.length() + 1, vector<int>(s2.length() + 1, 0));
    for (auto i = 1; i < d.size(); i++)
    {
        for (auto j = 1; j < d[0].size(); j++)
        {
            auto x1 = d[i - 1][j - 1] + matrix[getId(s1[i - 1])][getId(s2[j - 1])];
            auto x2 = d[i - 1][j] + gap;
            auto x3 = d[i][j - 1] + gap;
            auto x4 = 0;
            if (x1 >= x2 && x1 >= x3 && x1 >= x4)
            {
                d[i][j] = x1;
                continue;
            }
            if (x2 >= x1 && x2 >= x3 && x2 >= x4)
            {
                d[i][j] = x2;
                continue;
            }
            if (x3 >= x1 && x3 >= x2 && x3 >= x4)
            {
                d[i][j] = x3;
                continue;
            }
            if (x4 >= x1 && x4 >= x2 && x4 >= x3)
            {
                d[i][j] = 0;
                continue;
            }
        }
    }
    ofstream out;
    out.open("output.txt");
    int cur_i, cur_j;
    auto best = 0;
    for (auto i = 0; i < s1.length() + 1; i++)
    {
        for (auto j = 0; j < s2.length() + 1; j++)
        {
            if (d[i][j] >= best)
            {
                best = d[i][j];
                cur_i = i;
                cur_j = j;
            }
        }
    }
    out << best << endl;
    string res1, res2;
    while (cur_i >= 1 && cur_j >= 1)
    {
        auto x1 = d[cur_i - 1][cur_j - 1] + matrix[getId(s1[cur_i - 1])][getId(s2[cur_j - 1])];
        auto x2 = d[cur_i - 1][cur_j] + gap;
        auto x3 = d[cur_i][cur_j - 1] + gap;
        auto x4 = 0;
        if (d[cur_i][cur_j] == x1)
        {
            res1 = s1[cur_i - 1] + res1;
            res2 = s2[cur_j - 1] + res2;
            cur_i -= 1;
            cur_j -= 1;
            continue;
        }
        if(d[cur_i][cur_j] == x2)
        {
            res1 = s1[cur_i - 1] + res1;
            res2 = "-" + res2;
            cur_i -= 1;
            continue;
        }
        if (d[cur_i][cur_j] == x3)
        {
            res1 = "-" + res1;
            res2 = s2[cur_j - 1] + res2;
            cur_j -= 1;
            continue;
        }
        if (d[cur_i][cur_j] == x4)
            break;
    }
    out << res1 << endl;
    out << res2;
    out.close();
}

int main()
{
    local_score();
    return 0;
}