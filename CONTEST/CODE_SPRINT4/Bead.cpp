#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


vector<vector<int> > posis[1 << 9][10];
bool caled[1 << 9][10];

vector<int> nowPath;

void printvi(vector<int>& p)
{
    for (int i = 0; i < p.size(); ++i) cout << p[i] << " ";
    cout << endl;
}

int total = 0;
void GenPossibles(int s, int remain)
{
    if (remain == 1)
    {
        nowPath.push_back(s);
        total++;
        nowPath.pop_back();
    }
    else
    {
        for (int i = 0; i <= s; ++i)
            if ((s | i) == s)
            {
                nowPath.push_back(i);
                GenPossibles(s - i, remain - 1);
                nowPath.pop_back();
            }
    }
}

int main()
{
    GenPossibles(511, 6);
    cout << total << endl;
    return 0;
}