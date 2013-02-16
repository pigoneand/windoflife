
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <map>
#include <set>
#include <utility>

using namespace std;

int N;
vector<int> a;

void readProblem()
{
    cin >> N;
    a.resize(N);
    for (int i = 0; i < N; ++i) cin >> a[i];
}

long long solveProblem()
{
    long long ans = 0;
    long long currentEdges = 0;
    
    for (int i = 0; i < N; ++i)
    {
        int nowEdge = a[i] + 1;
        for (int j = 1; j <= nowEdge; ++j)
        {
            long long currentPlus = currentEdges;
            if (j >= 3) currentPlus += (j - 2);
            ans += currentPlus;
        }
        ans++;
        if (i == 0) ans++;
        currentEdges += nowEdge;
    }
    return ans;
}

int main()
{
    freopen("/Users/pigoneand/Desktop/cake_cutting.txt", "r", stdin);
    freopen("/Users/pigoneand/Desktop/cake_cutting.out", "w", stdout);
    
    int tests;
    cin >> tests;
    string line;
    getline(cin, line);
    for (int i = 1; i <= tests; ++i)
    {
        readProblem();
        long long ans = solveProblem();
        printf("Case #%d: ", i);
        cout << ans << endl;
    }
}
