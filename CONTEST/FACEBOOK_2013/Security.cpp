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

class BipartiteMaxMatch
{
public:
    /** Max Left or Right Nodes */
    static const int MaxN = 250;
    
    int leftNodes;
    int rightNodes;
    
    /** These is an edge between left node i and right node j */
    bool connect[MaxN][MaxN];
    
    /** Left i's current partener */
    int leftPart[MaxN];
    
    /** Right i's current partener */
    int rightPart[MaxN];
    
    /** Right Node Visited or not */
    bool visited[MaxN];
    
    BipartiteMaxMatch(int left, int right)
    {
        if (left > MaxN || right > MaxN) {
            cerr << "Too much nodes" << endl;
            return;
        }
        leftNodes = left;
        rightNodes = right;
        memset(connect, false, sizeof(connect));
    }
    
    /** Start Match */
    int match()
    {
        int ans = 0;
        for (int i = 0; i < leftNodes; ++i) leftPart[i] = -1;
        for (int j = 0; j < rightNodes; ++j) rightPart[j] = -1;
        memset(visited, false, sizeof(visited));
        
        for (int i = 0; i < leftNodes; ++i)
            if (leftPart[i] == -1) {
                memset(visited, false, sizeof(visited));
                ans += find(i);
            }
        return ans;
    }
    
    /** Find the augument path */
    int find(int start)
    {
        for (int i = 0; i < rightNodes; ++i) {
            if (!visited[i] && connect[start][i]) {
                visited[i] = true;
                if (rightPart[i] == -1 || find(rightPart[i])) {
                    leftPart[start] = i;
                    rightPart[i] = start;
                    return 1;
                }
            }
        }
        return 0;
    }
};

///////////////////
//
///////////////////

int M;
int L;
string k1, k2;

void readProblem()
{
    cin >> M;
    cin >> k1 >> k2;
}

bool couldMatch(const string& s1, const string& s2)
{
    for (int i = 0; i < s1.length(); ++i)
    {
        if (s1[i] == '?' || s2[i] == '?')
            continue;
        if (s1[i] != s2[i]) return false;
    }
    return true;
}

bool findMatch()
{
    BipartiteMaxMatch* g = new BipartiteMaxMatch(M, M);
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < M; ++j)
        {
            string s1 = k1.substr(i * L, L);
            string s2 = k2.substr(j * L, L);
            if (couldMatch(s1, s2)) g->connect[i][j] = true;
        }
    int maxMacth = g->match();
    delete g;
    return maxMacth == M;
}

string solveProblem()
{
    L = (int) k1.length() / M;
    
    for (int i = 0; i < k1.length(); ++i)
    {
        if (k1[i] == '?')
            for (k1[i] = 'a'; k1[i] <= 'f'; ++k1[i])
                if (findMatch())
                    break;
    }
    
    if (findMatch())
        return k1;
    else
        return "IMPOSSIBLE";
}

int main()
{    
    freopen("/Users/pigoneand/Desktop/security.txt", "r", stdin);
    freopen("/Users/pigoneand/Desktop/security.out", "w", stdout);
    
    int tests;
    cin >> tests;
    string line;
    getline(cin, line);
    
    for (int i = 1; i <= tests; ++i)
    {
        readProblem();
        string ans = solveProblem();
        printf("Case #%d: %s\n", i, ans.data());
    }
}
