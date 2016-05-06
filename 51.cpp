#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class el
{
public:
    int c;
    int i;
    int j;
};

void lcs()
{
    ifstream in;
    in.open("input.txt");
    string s1, s2;
    in >> s1 >> s2;
    in.close();
    vector<vector<el>> d(s1.length() + 1, vector<el>(s2.length() + 1));
    for (auto i = 0; i < s1.length() + 1; i++)
    {
        for (auto j = 0; j < s2.length() + 1; j++)
        {
            el tmp;
            if (i == 0 || j == 0)
            {
                tmp.c = 0;
                tmp.i = 0;
                tmp.j = 0;
                d[i][j] = tmp;
                continue;
            }
            if (s1[i - 1] == s2[j - 1])
            {
                tmp.c = d[i - 1][j - 1].c + 1;
                tmp.i = i - 1;
                tmp.j = j - 1;
                d[i][j] = tmp;
                continue;
            }
            if (s1[i - 1] != s2[j - 1])
            {
                if (d[i - 1][j].c > d[i][j - 1].c)
                {
                    tmp.c = d[i - 1][j].c;
                    tmp.i = i - 1;
                    tmp.j = j;
                }
                else
                {
                    tmp.c = d[i][j - 1].c;
                    tmp.i = i;
                    tmp.j = j - 1;
                }
                d[i][j] = tmp;
                continue;
            }
        }
    }
    string res = "";
    auto i = s1.length();
    auto j = s2.length(); 
    while (true)
    {
        if (d[i][j].i == i - 1 && d[i][j].j == j - 1)
            res = s1[i - 1] + res;
        auto newi = d[i][j].i;
        auto newj = d[i][j].j;
        i = newi;
        j = newj;
        if (i == 0 && j == 0)
            break;
    }
    cout << res << endl;
}

int main()
{
    lcs();
    return 0;
}