#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <set>
#include <vector>
#include <map>
#include <cmath>
#include <unordered_map>

using namespace std;

bool try_ass(vector<vector<int>>& dor, map<int, int, greater<int>> dist, int leftpos, int downpos)
{
//    cout << "dist size:" << dist.size() << endl;
//    for (auto x : dist)
//        cout << x.first<< ":" << x.second << " ";
//    cout << endl;
//    for (auto x : dor)
//    {
//        for (auto y : x)
//            cout << y << "\t";
//        cout << endl;
//    }
//    cout << endl;
    if (dist.empty())
    {
        for (auto x : dor[0])
            cout << x << " ";
        cout << endl;
        return true;
    }

    auto it = dist.begin();
    auto cur = it->first;
    //left
    if (leftpos > 0)
    {
        auto d = dor;
  //      cout << "left: left = " << leftpos << " down = " << downpos << " cur = " << cur << endl;
        d[0][leftpos] = cur;
        auto newone = d[0][leftpos + 1] - d[0][leftpos];
        auto newdist = dist;
        auto it2 = newdist.find(cur);
        if (it2->second == 1)
            newdist.erase(it2);
        else
            it2->second--;
        auto flag = false;
	if (d[leftpos][leftpos + 1] == newone)
		flag = true;
        it2 = newdist.find(newone);
        if (!flag && it2 != newdist.end())
        {
            d[leftpos][leftpos + 1] = newone;
            if (it2->second == 1)
                newdist.erase(it2);
            else
                it2->second--; 
 	    flag = true;
        }
        if (flag)
        {
    //        cout << "here_left" << endl;
            for (auto i = 1; i < min(downpos, leftpos - 1); i++)
            {
                auto newval = d[i][leftpos + 1] - newone;
	//        cout << "newval left = " << newval << endl;        
		auto itc = newdist.find(newval);
                if (itc != newdist.end())
                {
                    if (itc->second == 1)
                        newdist.erase(itc);
                    else
                        itc->second--;
                    d[i][leftpos] = newval;
                }
                else if (d[i][leftpos] != newval)
                    flag = false;
            }
        }
        if (flag)
            if (try_ass(d, newdist, leftpos - 1, downpos))
                return true;
    }
    //down
    if (downpos < dor.size() - 1)
    {
        auto d = dor;
       // cout << "down: left = " << leftpos << " down = " << downpos << " cur = " << cur << endl;
        d[downpos][d.size() - 1] = cur;
        auto newone = d[downpos - 1][d.size() - 1] - d[downpos][d.size() - 1];
        auto newdist = dist;
        auto it2 = newdist.find(cur);
        if (it2->second == 1)
            newdist.erase(it2);
        else
            it2->second--;
        auto flag = false;
	if (d[downpos - 1][downpos] == newone)
		flag = true;
        it2 = newdist.find(newone);
        if (!flag && it2 != newdist.end())
        {
            d[downpos - 1][downpos] = newone;
            if (it2->second == 1)
                newdist.erase(it2);
            else
                it2->second--;
	    flag = true;
        }
        if (flag)
        {
            for (auto i = max(leftpos + 1, downpos + 2); i < d.size() - 1; i++)
            {
                auto newval = d[downpos - 1][i] - newone;
	//	cout << "newval right = " << newval << endl;                
		auto itc = newdist.find(newval);
                if (itc != newdist.end())
                {
                    if (itc->second == 1)
                        newdist.erase(itc);
                    else
                        itc->second--;
                    d[downpos][i] = newval;
                }
                else if (d[downpos][i] != newval)
                    flag = false;
            }
        }
        if (flag)
            if(try_ass(d, newdist, leftpos, downpos + 1))
                return true;
    }
    return false;
}

void turnpike()
{
    ifstream in;
    in.open("rosalind_ba4m.txt");
    map<int, int, greater<int>> dist;
    int tmp;
    auto max = 0;
    auto n = 0;
    while (in >> tmp)
    {
        if (tmp > max)
            max = tmp;
        if (tmp == 0)
            n++;
        if (tmp > 0)
        {
            auto it = dist.find(tmp);
            if (it == dist.end())
                dist[tmp] = 1;
            else
                dist[tmp]++;
        }
    }
    in.close();

    vector<vector<int>> d(n);
    for (auto i = 0; i < n; i++)
        d[i] = vector<int>(n, 0);
    d[0][n - 1] = max;
    dist.erase(dist.find(max));
    try_ass(d, dist, n - 2, 1);
}


int main()
{
    turnpike();
    return 0;
}