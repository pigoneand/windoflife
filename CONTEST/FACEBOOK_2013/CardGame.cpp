//
//  main.cpp
//  test
//  Created by 朱 一和 on 13-1-20.
//

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

int N, K;
const int MODER = 1000000007;
vector<int> a;

int C[10001][10001];

void init()
{
    memset(C, 0, sizeof(C));
    C[0][0] = 1;
    C[1][0] = C[1][1] = 1;
    for (int i = 2; i <= 10000; ++i)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MODER;
    }
}

void readProblem()
{
    cin >> N >> K;
    a.resize(N);
    for (int i = 0; i < N; ++i)
        cin >> a[i];
}

int solveProblem()
{
    sort(a.begin(), a.end(), greater<int>());

    long long ans = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        long long now = a[i];
        long long ways = C[N - i - 1][K - 1];
        ans += now * ways;
        ans %= MODER;
    }
    return (int) ans;
}

int main()
{
    init();
    
    freopen("/Users/pigoneand/Desktop/card_game.txt", "r", stdin);
    freopen("/Users/pigoneand/Desktop/card_game.out", "w", stdout);
    
    int tests;
    cin >> tests;
    string line;
    getline(cin, line);
    for (int i = 1; i <= tests; ++i)
    {
        readProblem();
        int ans = solveProblem();
        printf("Case #%d: %d\n", i, ans);
    }
}
