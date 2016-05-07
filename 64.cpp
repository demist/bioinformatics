#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int number(vector<int>& per)
{
    int res = 0;
    if (per[0] != 1)
        res++;
    if (per[per.size() - 1] != per.size())
        res++;
    for (auto i = 0; i < per.size() - 1; i++)
        if (abs(per[i + 1] - per[i]) != 1 || per[i + 1] < per[i])
            res++;
    return res;
}

int main()
{
    ifstream in;
    in.open("input.txt");
    vector<int> per;
    int tmp;
    char a;
    in >> a;
    while (in >> a >> tmp)
    {
        if (a == '+')
            per.push_back(tmp);
        else
            per.push_back(-1 * tmp);
    }
    cout << number(per) << endl;
    return 0;
}