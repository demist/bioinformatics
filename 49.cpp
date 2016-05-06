#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <vector>

using namespace std;

void change()
{
    ifstream in;
    in.open("input.txt");
    vector<int> coins;
    int sum;
    in >> sum;
    int tmp;
    while (in >> tmp)
        coins.push_back(tmp);
    in.close();

    vector<vector<int>> m(coins.size() + 1, vector<int>(sum + 1, 0));
    for (auto i = 0; i < sum + 1; i++)
        m[0][i] = i;
    for (auto c = 1; c < coins.size() + 1; c++)
    {
        for (auto r = 0; r < sum + 1; r++)
        {
            if (coins[c - 1] == r)
                m[c][r] = 1;
            else
            {
                if (coins[c - 1] > r)
                    m[c][r] = m[c - 1][r];
                else
                    m[c][r] = min(m[c - 1][r], 1 + m[c][r - coins[c - 1]]);
            }
        }
    }
    cout << m[coins.size()][sum] << endl;
}

int main()
{
    change();
    return 0;
}