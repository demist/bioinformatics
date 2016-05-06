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

int t_max(int a, int b, int c)
{
  if (a >= b && a >= c)
    return a;
  if (b >= a && b >= c)
    return b;
  else return c;
}

int index(int a, int b, int c)
{
  if (a >= b && a >= c)
    return 0;
  if (b >= a && b >= c)
    return 1;
  else
    return 2;
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
    auto o_gap = -11;
    auto ex_gap = -1;
    vector<vector<int>> M(s1.length() + 1, vector<int>(s2.length() + 1, 0));
    vector<vector<int>> X(s1.length() + 1, vector<int>(s2.length() + 1, 0));    
    vector<vector<int>> Y(s1.length() + 1, vector<int>(s2.length() + 1, 0));
    vector<vector<int>> M1(s1.length() + 1, vector<int>(s2.length() + 1, 0));
    vector<vector<int>> X1(s1.length() + 1, vector<int>(s2.length() + 1, 0));
    vector<vector<int>> Y1(s1.length() + 1, vector<int>(s2.length() + 1, 0));
    for (auto i = 1; i < s1.length() + 1; i++)
    {
      for (auto j = 1; j < s2.length() + 1; j++)
      {
	M[i][j] = matrix[getId(s1[i - 1])][getId(s2[j - 1])] + t_max(M[i - 1][j - 1], X[i - 1][j - 1], Y[i - 1][j - 1]);
	M1[i][j] = index(M[i - 1][j - 1], X[i - 1][j - 1], Y[i - 1][j - 1]);
	X[i][j] = t_max(o_gap + M[i][j - 1], ex_gap + X[i][j - 1], o_gap + Y[i][j - 1]);
	X1[i][j] = index(o_gap + M[i][j - 1], ex_gap + X[i][j - 1], o_gap + Y[i][j - 1]);
	Y[i][j] = t_max(o_gap + M[i - 1][j], o_gap + X[i - 1][j], ex_gap + Y[i - 1][j]);
	Y1[i][j] = index(o_gap + M[i - 1][j], o_gap + X[i - 1][j], ex_gap + Y[i - 1][j]);
      }
    }
    ofstream out;
    out.open("output.txt");
    auto cur_i = s1.length();
    auto cur_j = s2.length();
    string res1, res2;
    out << t_max(M[cur_i][cur_j], X[cur_i][cur_j], Y[cur_i][cur_j]) << endl;
    auto matr = index(M[cur_i][cur_j], X[cur_i][cur_j], Y[cur_i][cur_j]);
    while (cur_i != 0 && cur_j != 0)
    {
      if (matr == 0)
      {
	auto newind = M1[cur_i][cur_j];
	res1 = s1[cur_i - 1] + res1;
	res2 = s2[cur_j - 1] + res2;
	cur_i--;
	cur_j--;
	matr = newind;
	continue;
      }
      if (matr == 1)
      {
	auto newind = X1[cur_i][cur_j];
	res1 = "-" + res1;
	res2 = s2[cur_j - 1] + res2;
	cur_j--;
	matr = newind;
	continue;
      }
      if (matr == 2)
      {
	auto newind = Y1[cur_i][cur_j];
	res1 = s1[cur_i - 1] + res1;
	res2 = "-" + res2;
	cur_i--;
	matr = newind;
	continue;
      }
    }
    out << res1 << endl << res2;
}

int main()
{
    score();
    return 0;
}