#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void getOverlap()
{
    ifstream in;
    in.open("input.txt");
    vector<string> kmers;
    string tmp;
    while (in >> tmp)
        kmers.push_back(tmp);
    in.close();
    ofstream out;
    out.open("output.txt");
    for (auto i = 0; i < kmers.size(); i++)
    {
        for (auto j = 0; j < kmers.size(); j++)
            if (i != j && kmers[i].substr(0, kmers[i].length() - 1) == kmers[j].substr(1, kmers[j].length() - 1))
                out << kmers[i] << " -> " << kmers[j] << endl;
    }
    out.close();
}

int main()
{
    getOverlap();
    return 0;
}