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

void score()
{
    ifstream in;
    in.open("input.txt");
    string s1, s2, s3, s4;
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
    vector<vector<int>> d(s1.length() + 1, vector<int>(s2.length() + 1));
    //initialize
    d[0][0] = 0;
    for (auto i = 1; i < d.size(); i++)
        d[i][0] = d[i - 1][0] + gap;
    for (auto j = 1; j < d[0].size(); j++)
        d[0][j] = d[0][j - 1] + gap;

    for (auto i = 1; i < d.size(); i++)
    {
        for (auto j = 1; j < d[0].size(); j++)
        {
            auto x1 = d[i - 1][j - 1] + matrix[getId(s1[i - 1])][getId(s2[j - 1])];
            auto x2 = d[i - 1][j] + gap;
            auto x3 = d[i][j - 1] + gap;
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
    ofstream out;
    out.open("output.txt");
    auto cur_i = d.size() - 1;
    auto cur_j = d[0].size() - 1;
    out << d[cur_i][cur_j] << endl;
    string res1, res2;
    while (cur_i >= 1 && cur_j >= 1)
    {
        auto x1 = d[cur_i - 1][cur_j - 1] + matrix[getId(s1[cur_i - 1])][getId(s2[cur_j - 1])];
        auto x2 = d[cur_i - 1][cur_j] + gap;
        auto x3 = d[cur_i][cur_j - 1] + gap;
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
    }
    while (cur_i >= 1)
    {
        res1 = s1[cur_i - 1] + res1;
        res2 = "-" + res2;
        cur_i--;
    }
    while (cur_j >= 1)
    {
        res1 = "-" + res1;
        res2 = s2[cur_j - 1] + res2;
        cur_j--;
    }
    out << res1 << endl;
    out << res2;
    out.close();
}

int main()
{
    score();
    return 0;
}