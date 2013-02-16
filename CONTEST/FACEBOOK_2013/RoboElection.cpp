
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

long long N, K, P;

void readProblem()
{
    cin >> N >> K >> P;
}

long long solveProblem()
{
    long long initN = N % K;
    if (initN == 0) initN = K;
    
    if (P == 100)
    {
        return (N - initN) / K + 1;
    }
    
    if (initN == N)
        return 1;
        
    long long a = initN;
    while (true)
    {
        long long x1 = P * a;
        long long x2 = K * (100 - P);
        long long x = x1 / x2;
        if (x1 % x2 != 0) x++;
        
        //cout << a << " " << x1 << " " << x2 << " " << x << endl;
        long long na = a + K * x;
        if (na >= N)
        {
            if (na == N) return 1;
            else return 1 + (N - a) / K;
        }
        a = na;
    }
}

int main()
{
    freopen("/Users/pigoneand/Desktop/roboelection.txt", "r", stdin);
    freopen("/Users/pigoneand/Desktop/roboelection.out", "w", stdout);
    
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
        cerr << i << endl;
    }
}
