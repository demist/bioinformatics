#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void probability()
{
    string res;
    ifstream in;
    in.open("input.txt");
    string dna;
    in >> dna;
    int k;
    in >> k;
    vector<vector<double>> matrix;
    matrix.resize(4);
    for (auto i = 0; i < 4; i++)
    {
        matrix[i].resize(k);
        for (auto j = 0; j < k; j++)
            in >> matrix[i][j];
    }
    in.close();
    auto max = -1.;
    for (auto i = 0; i <= dna.length(); i++)
    {
        auto cur = 1.;
        for (auto j = 0; j < k; j++)
        {
            int index;
            switch (dna[i + j])
            {
                case 'A':
                    index = 0;
                    break;
                case 'C':
                    index = 1;
                    break;
                case 'G':
                    index = 2;
                    break;
                case 'T':
                    index = 3;
                    break;
                default:
                    break;
            }
            cur *= matrix[index][j];
        }
        if (cur > max)
        {
            res = dna.substr(i, k);
            max = cur;
        }
    }
    cout << res << endl;
}

int main()
{
    probability();
    return 0;
}