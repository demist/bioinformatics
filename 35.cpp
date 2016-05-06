#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <sstream>

using namespace std;

void allmax()
{
    ifstream in;
    in.open("input.txt");
    char buff[256];
    map<int, list<int>> gr;
    map<int, int> indeg;
    while (in.getline(buff, 256))
    {
        istringstream inp(buff);
        int v1, v2;
        inp >> v1;
        while (inp >> v2)
        {
            gr[v1].push_back(v2);
            if (indeg.find(v2) == indeg.end())
                indeg[v2] = 1;
            else
                indeg[v2]++;
        }
    }
    in.close();

    list<list<int>> paths;
    
    for (auto v : gr)
    {
        if (!(v.second.size() == 1 && indeg[v.first] == 1))
        {
            if (v.second.size() > 0)
            {
                for (auto w : v.second)
                {
                    list<int> newpath;
                    newpath.push_back(v.first);
                    newpath.push_back(w);
                    while (gr[w].size() == 1 && indeg[w] == 1)
                    {
                        auto u = gr[w].front();
                        newpath.push_back(u);
                        w = u;
                    }
                    if (!newpath.empty())
                        paths.push_back(newpath);
                }
            }
        }
    }

    for (auto v : gr)
    {
        if (v.second.size() == 1 && indeg[v.first] == 1)
        {
            list<int> cycle;
            cycle.push_back(v.first);
            auto w = v.second.front();
            while (gr[w].size() == 1 && indeg[w] == 1)
            {
                cycle.push_back(w);
                if (w == v.first)
                {
                    paths.push_back(cycle);
                    for (auto x : cycle)
                    {
                        auto it = gr.find(x);
                        it->second.clear();
                    }
                    break;
                }
                w = gr[w].front();
            }
        }
    }
    ofstream out;
    out.open("output.txt");
    for (auto p : paths)
    {
        while (!p.empty())
        {
            out << p.front();
            if (p.size() != 1)
                out << " -> ";
            p.pop_front();
        }
        out << endl;
    }
    out.close();
}

int main()
{
    allmax();
    return 0;
}