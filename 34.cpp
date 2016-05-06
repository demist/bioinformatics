#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

void construct()
{
    ifstream in;
    in.open("input.txt");
    list<string> kmers;
    string t1, t2;
    int k, d;
    in >> k >> d;
    while (in >> t1 >> t2)
        kmers.push_back(t1 + t2);
    in.close();
    string res(2 * k + d + kmers.size() - 1, 'A');
    auto cnt = 0;
    for (auto x : kmers)
    {
        for (auto j = 0; j < k; j++)
            res[cnt + j] = x[j];
        for (auto j = 0; j < k; j++)
            res[cnt + k + d + j] = x[k + j];
        cnt++;
    }
        
    cout << res << endl;
}

int main()
{
    construct();
    return 0;
}