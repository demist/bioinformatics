#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> weights = {57,71,87,97,99,101,103,113,114,115,128,129,131,137,147,156,163,186};

class longholder
{
public:
     unsigned long long value;
};

int count(int mass)
{
    unordered_map<int, longholder*> vars;
    auto tmp = new longholder();
    tmp->value = 1;
    vars.insert(make_pair(0, tmp));
    for (auto cur_mass = 0; cur_mass <= mass; cur_mass++)
    {
        for (auto i = 0; i < weights.size(); i++)
        {
            auto needed_mass = cur_mass - weights[i];
            auto it = vars.find(needed_mass);
            if (it != vars.end())
            {
                auto it2 = vars.find(cur_mass);
                if (it2 == vars.end())
                {
                    auto t = new longholder();
                    t->value = it->second->value;
                    vars.insert(make_pair(cur_mass, t));
                }
                else 
                {
                    auto t = new longholder();
                    t->value = it2->second->value + it->second->value;
                    it2->second = t;
                }
            }
        }
    }
    return vars[mass]->value;
}


int main()
{
    int a;
    cin >> a;
    cout << count(a) << endl;
    return 0;
}