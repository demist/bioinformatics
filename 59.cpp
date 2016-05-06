#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int gap = -5;
vector<vector<int>> matrix(20, vector<int>(20));

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

void loadMatrix()
{
    ifstream in;
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
}

void score(string v, string w, vector<int>& last_line, vector<int>& backtrack)
{
    vector<int> cur_line(v.length() + 1, 0);
    vector<int> next_line(v.length() + 1, 0);
    backtrack.resize(v.length() + 1);
    for (auto i = 1; i < cur_line.size(); i++)
        cur_line[i] = cur_line[i - 1] + gap;
    for (auto j = 0; j < w.length(); j++)
    {
        for (auto i = 0; i < cur_line.size(); i++)
        {
            if (i == 0)
            {
                next_line[i] = cur_line[i] + gap;
                backtrack[i] = 2;
                continue;
            }
            auto x1 = cur_line[i - 1] + matrix[getId(v[i - 1])][getId(w[j])]; //i - 1 j -1
            auto x2 = next_line[i - 1] + gap; // i - 1
            auto x3 = cur_line[i] + gap; // j - 1
            if (x1 >= x2 && x1 >= x3)
            {
                next_line[i] = x1;
                backtrack[i] = 0;
                continue;
            }
            if (x2 >= x1 && x2 >= x3)
            {
                next_line[i] = x2;
                backtrack[i] = 1;
                continue;
            }
            if (x3 >= x1 && x3 >= x2)
            {
                next_line[i] = x3;
                backtrack[i] = 2;
                continue;
            }
        }
        cur_line = next_line;
    }
    last_line = cur_line;
}

void find()
{
    ifstream in;
    in.open("input.txt");
    string s1, s2;
    in >> s1 >> s2;
    in.close();

    vector<int> forward, backward, bt1, bt2;
    int m = s2.length() / 2 == 0 ? s2.length() / 2 : s2.length() / 2 + 1;
    score(s1, s2.substr(0, m), forward, bt1);

    auto s1r = s1;
    for (auto i = 0; i < s1.length(); i++)
        s1r[s1r.length() - 1 - i] = s1[i];
    auto s2r = s2.substr(m);
    for (auto i = 0; i < s2r.length(); i++)
        s2r[s2r.length() - 1 - i] = s2[m + i];
    score(s1r, s2r, backward, bt2);

    auto best = -1000000;
    int x;
    for (auto i = 0; i < s1.length(); i++)
    {
        auto cur = forward[i] + backward[backward.size() - 1 - i];
        if (cur > best)
        {
            x = i;
            best = cur;
        }
    }
    int y = m;
    int xf, yf;
    if (bt1[x] == 0)
    {
        xf = x - 1;
        yf = y - 1;
    }
    if (bt1[x] == 1)
    {
        xf = x - 1;
        yf = y;
    }
    if (bt1[x] == 2)
    {
        xf = x;
        yf = y - 1;
    }
    cout << "(" << xf << ", " << yf << ") (" << x << ", " << y << ")" << endl;
}

int main()
{
    loadMatrix();
    find();
    return 0;
}