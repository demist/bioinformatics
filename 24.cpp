#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void getGenome()
{
    ifstream in;
    in.open("input.txt");
    vector<string> kmers;
    string tmp;
    while (in >> tmp)
        kmers.push_back(tmp);
    in.close();
    string res(kmers.size() + kmers[0].length() - 1, 'A');
    for (auto i = 0; i < kmers.size(); i++)
        res[i] = kmers[i][0];
    for (auto i = 1; i < kmers[kmers.size() - 1].length(); i++)
        res[kmers.size() - 1 + i] = kmers[kmers.size() - 1][i];
    ofstream out;
    out.open("output.txt");
    out << res << endl;
    out.close();
}

int main()
{
    getGenome();
    return 0;
}