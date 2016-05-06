#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void edit_dist()
{
    ifstream in;
    in.open("input.txt");
    string s1, s2;
    in >> s1 >> s2;
    in.close();

    vector<vector<int>> d(s1.length() + 1, vector<int>(s2.length() + 1, 0));
    for (auto i = 0; i < s1.length() + 1; i++)
    {
        for (auto j = 0; j < s2.length() + 1; j++)
        {
            if (i == 0 && j == 0)
                d[i][j] = 0;
            if (i > 0 && j == 0)
                d[i][j] = i;
            if (i == 0 && j > 0)
                d[i][j] = j;
            if (i > 0 && j > 0)
            {
                auto x1 = d[i][j - 1] + 1;
                auto x2 = d[i - 1][j] + 1;
                auto m = s1[i - 1] == s2[j - 1] ? 0 : 1;
                auto x3 = d[i - 1][j - 1] + m;
                if (x1 <= x2 && x1 <= x3)
                    d[i][j] = x1;
                if (x2 <= x1 && x2 <= x3)
                    d[i][j] = x2;
                if (x3 <= x1 && x3 <= x2)
                    d[i][j] = x3;
            }
        }
    }
    cout << d[d.size() - 1][d[0].size() - 1] << endl;
}

int main()
{
    edit_dist();
    return 0;
}