#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void ch2c()
{
    ifstream in("input.txt");
    char ct;
    int tmp;
    in >> ct;
    vector<int> g;
    while (in >> ct >> tmp)
        g.push_back(ct == '+' ? tmp : -1 * tmp);
    in.close();

    vector<int> result;
    for (auto i = 0; i < g.size(); i++)
    {
        if (g[i] > 0)
        {
            result.push_back(2 * g[i] - 1);
            result.push_back(2 * g[i]);
        }
        else
        {
            result.push_back(-2 * g[i]);
            result.push_back(-2 * g[i] - 1);
        }
    }
    cout << "(";
    for (auto x : result)
        cout << x << " ";
    cout << ")" << endl;
}

int main()
{
    ch2c();
    return 0;
}