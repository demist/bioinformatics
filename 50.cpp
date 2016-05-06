#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void longest()
{
    ifstream in;
    in.open("input.txt");
    int n, m;
    in >> n >> m;
    vector<vector<int>> down(n, vector<int>(m + 1));
    int tmp;
    for (auto i = 0; i < n; i++)
    {
        for (auto j = 0; j < m + 1; j++)
        {
            in >> tmp;
            down[i][j] = tmp;
        }
    }
    vector<vector<int>> right(n + 1, vector<int>(m));
    for (auto i = 0; i < n + 1; i++)
    {
        for (auto j = 0; j < m; j++)
        {
            in >> tmp;
            right[i][j] = tmp;
        }
    }
    in.close();

    vector<vector<int>> matrix(n + 1, vector<int>(m + 1, 0));
    for (auto i = 0; i < n + 1; i++)
    {
        for (auto j = 0; j < m + 1; j++)
        {
            if (i > 0 && j > 0) 
                matrix[i][j] = max(matrix[i - 1][j] + down[i - 1][j], matrix[i][j - 1] + right[i][j - 1]);
            if (i > 0 && j == 0)
                matrix[i][j] = matrix[i - 1][j] + down[i - 1][j];
            if (i == 0 && j > 0)
                matrix[i][j] = matrix[i][j - 1] + right[i][j - 1];
        }
    }
    cout << matrix[n][m] << endl;
}

int main()
{
    longest();
    return 0;
}