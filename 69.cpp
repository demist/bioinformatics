#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void c2ch()
{
    ifstream in("input.txt");
    int tmp;
    vector<int> c;
    while (in >> tmp)
        c.push_back(tmp);
    in.close();
    
    vector<int> result;
    for (auto i = 0; i < c.size() / 2; i++)
    {
        int s;
        if (c[2 * i] < c[2 * i + 1])
            s = i + 1;
        else
            s = -1 * (i + 1);
        result.push_back(s);
    }
    cout << "(";
    for (auto x : result)
        cout << (x > 0 ? "+" : "") << x << " ";
    cout << endl;
}

int main()
{
    c2ch();
    return 0;
}