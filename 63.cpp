#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int getId (int a, vector<int>& vec)
{
    int res = -1;
    for (auto i = 0; i < vec.size(); i++)
        if (vec[i] == a)
            res = i;
    return res;
}

void reverse(int from, int to, vector<int>& vec)
{
    auto cp = vec;
    for (auto i = 0; i < to - from; i++)
        vec[from + i] = -1 * cp[to - i - 1];
}

void greedy()
{
    ifstream in;
    in.open("input.txt");
    vector<int> per;
    int tmp;
    while (in >> tmp)
        per.push_back(tmp);
    in.close();
    ofstream out;
    out.open("output.txt");
    for (auto i = 0; i < per.size(); i++)
    {
        if (per[i] != i + 1)
        {
            auto id = getId(i + 1, per) != -1 ? getId(i + 1, per) : getId(-1 * (i + 1), per);
            reverse(i, id + 1, per);
            out << "(";
            for (auto i = 0; i < per.size(); i++)
            {
                out << (per[i] >= 0 ? "+" : "-") << abs(per[i]);
                if (i != per.size() - 1)
                    out << " ";
            }
            out << ")" << endl;
        }
        if (per[i] == -1 * (i + 1))
        {
            per[i] = i + 1;
            out << "(";
            for (auto i = 0; i < per.size(); i++)
            {
                out << (per[i] >= 0 ? "+" : "-") << abs(per[i]);
                if (i != per.size() - 1)
                    out << " ";
            }
            out << ")" << endl;
        }
    }
    out.close();
}

int main()
{
    greedy();
    return 0;
}