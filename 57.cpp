#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string addIndel(string a, int pos)
{
    return a.substr(0, pos + 1) + "-" + a.substr(pos + 1);
}

void overlap()
{
    ifstream in;
    in.open("input.txt");
    string s1, s2;
    in >> s1 >> s2;
    in.close();
    
    vector<vector<int>> d(s1.length() + 1, vector<int>(s2.length() + 1, 0));
    int best = -10 * (s1.length() + s2.length());
    auto b_i = 0;
    auto b_j = 0;
    for (auto i = 1; i < s1.length() + 1; i++)
    {
        for (auto j = 1; j < s2.length() + 1; j++)
        {
            auto x1 = d[i - 1][j] - 2;
            auto x2 = d[i][j - 1] - 2;
            auto m = s1[i - 1] == s2[j - 1] ? 1 : -2;
            auto x3 = d[i - 1][j - 1] + m;
            if (x1 >= x2 && x1 >= x3)
                d[i][j] = x1;
            if (x2 >= x1 && x2 >= x3)
                d[i][j] = x2;
            if (x3 >= x1 && x3 >= x2)
                d[i][j] = x3;
	    if (i == s1.length() || j == s2.length())
	    {
	      if (d[i][j] > best)
	      {
		best = d[i][j];
		b_i = i;
		b_j = j;
	      }
	    }
        }
    }
    auto s1_al = s1.substr(0, b_i);
    auto s2_al = s2.substr(0, b_j);
    
    while (b_i != 0 && b_j != 0)
    {
	    auto x1 = d[b_i - 1][b_j] - 2;
            auto x2 = d[b_i][b_j - 1] - 2;
            auto m = s1[b_i - 1] == s2[b_j - 1] ? 1 : -2;
            auto x3 = d[b_i - 1][b_j - 1] + m;
            if (x1 >= x2 && x1 >= x3)
	    {
	      b_i -= 1;
	      s2_al = addIndel(s2_al, b_j - 1);
	      continue;
	    }
            if (x2 >= x1 && x2 >= x3)
	    {
	      b_j -= 1;
	      s1_al = addIndel(s1_al, b_i - 1);
	      continue;
	    }
            if (x3 >= x1 && x3 >= x2)
	    {
		b_i -= 1;
		b_j -= 1;
	    }
    }
    s1_al = s1_al.substr(b_i);
    s2_al = s2_al.substr(b_j);
    ofstream out;
    out.open("output.txt");
    out << best << endl;
    out << s1_al << endl << s2_al;
    out.close();
}

int main()
{
    overlap();
    return 0;
}