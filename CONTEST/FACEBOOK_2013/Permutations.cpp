

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
vector<pair<int, int> > edges;
vector<int> outEdges[1001];
long long moder = 1000000007;
long long C[1001][1001];

void init()
{
    memset(C, 0, sizeof(C));
    C[0][0] = 1;
    for (int i = 1; i <= 1000; ++i)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % moder;
    }
}

void readProblem()
{
    cin >> N;
    
    int a, b;
    string s;
    edges.clear();
    for (int i = 0; i < N; ++i) outEdges[i].clear();
    
    for (int i = 0; i < N - 1; i ++) {
        cin >> a >> s >> b;
        if (s == "<")
        {
            edges.push_back(make_pair(a, b));
            outEdges[a].push_back(b);
        }
        else
        {
            edges.push_back(make_pair(b, a));
            outEdges[b].push_back(a);
        }
    }
}

void dfs(int now, int parent, vector<bool>& visit, int& curSize)
{
    visit[now] = true;
    curSize++;
    for (int i = 0; i < outEdges[now].size(); ++i)
    {
        int nextID = outEdges[now][i];
        if (nextID != parent)
            dfs(nextID, now, visit, curSize);
    }
}

long long solveSet(vector<bool> isV)
{
    int validCnt = 0;
    for (int i = 0; i < N; ++i) if (isV[i]) validCnt++;
    if (validCnt == 0) return 1;
    if (validCnt == 1) return 1;
    
    vector<int> inDeg(N, 0);

    for (int i = 0; i < edges.size(); ++i)
    {
        int a = edges[i].first;
        int b = edges[i].second;
        if (isV[a] && isV[b]) inDeg[b]++;
    }
    
    long long ret = 0;
    
    for (int i = 0; i < N; ++i)
    {
        if (inDeg[i] == 0 && isV[i])
        {
            vector<pair<int, long long> > anss;
            for (int j = 0; j < outEdges[i].size(); ++j)
            {
                int nextID = outEdges[i][j];
                if (isV[nextID])
                {
                    vector<bool> subVisit(N, false);
                    int curSize = 0;
                    dfs(nextID, i, subVisit, curSize);
                    long long subAns = solveSet(subVisit);
                    anss.push_back(make_pair(curSize, subAns));
                }
            }
            sort(anss.begin(), anss.end(), greater<pair<int, long long> >());
            
            long long nowans = 1;
            for (int i = 0; i < anss.size(); ++i)
                nowans = nowans * anss[i].second % moder;
            
            int sum = 1;
            for (int i = 0; i < anss.size() - 1; ++i)
            {
                int key1 = anss[i].first;
                int key2 = anss[i + 1].first;
                sum += key1;
                nowans = nowans * C[sum][key2] % moder;
            }
            
            ret += nowans;
            ret %= moder;
        }
    }
    return ret;
}

long long solveProblem()
{
    vector<bool> isV(N, true);
    return solveSet(isV);
}

int main()
{
    freopen("/Users/pigoneand/Desktop/permutations.txt", "r", stdin);
    freopen("/Users/pigoneand/Desktop/permutations3.out", "w", stdout);
    init();
    
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
 

/*
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
typedef double du;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define FOR(i, s, t) for(i = (s); i < (t); i++)
#define RFOR(i, s, t) for(i = (s)-1; i >= (t); i--)
const int MAXN = 1004;
const int P = 1000000007;

int c[MAXN][MAXN];
int a[MAXN][MAXN];
int f[MAXN][MAXN];
int size[MAXN];
int s[MAXN], t[MAXN];
int n;

int foo(int i, int j){
    return c[i+j][i];
}

void dfs(int i){
    int j, k, l;
    size[i] = 1;
    memset(f[i], 0, sizeof f[i]);
    f[i][0] = 1;
    for(j = 0; j < n; j++)
        if(a[i][j] && size[j] == -1){
            dfs(j);
            memset(s, 0, sizeof s);
            memset(t, 0, sizeof t);
            if(a[i][j] == -1){
                s[size[j]-1] = f[j][size[j]-1];
                for(k = size[j]-2; k >= 0; k--)
                    s[k] = (s[k+1] + f[j][k]) % P;
                for(k = 0; k < size[i]; k++)
                    for(l = 0; l < size[j]; l++)
                        t[k+l] = (t[k+l] + (ll)f[i][k]*s[l]%P*foo(k, l)%P*foo(size[i]-k-1, size[j]-l)) % P;
            }
            else{
                s[1] = f[j][0];
                for(k = 2; k <= size[j]; k++)
                    s[k] = (s[k-1] + f[j][k-1]) % P;
                for(k = 0; k < size[i]; k++)
                    for(l = 1; l <= size[j]; l++)
                        t[k+l] = (t[k+l] + (ll)f[i][k]*s[l]%P*foo(k, l)%P*foo(size[i]-k-1, size[j]-l)) % P;
            }
            size[i] += size[j];
            for(k = 0; k < size[i]; k++)
                f[i][k] = t[k];
        }
}

int main()
{
//#ifdef __FIO
    freopen("/Users/pigoneand/Desktop/permutations.txt", "r", stdin);
    freopen("/Users/pigoneand/Desktop/permutations2.out", "w", stdout);
//#endif
    int T, i0;
    scanf("%d", &T);
    for(i0 = 1; i0 <= T; i0++){
        int i, j;
        int x, y;
        char sign;
        c[0][0] = 1;
        scanf("%d\n", &n);
        for(i = 1; i <= n; i++){
            c[i][0] = 1;
            for(j = 1; j <= i; j++)
                c[i][j] = (c[i-1][j-1] + c[i-1][j]) % P;
        }
        memset(a, 0, sizeof a);
        for(i = 1; i < n; i++){
            scanf("%d %c %d\n", &x, &sign, &y);
            if(sign == '>')
                swap(x, y);
            a[x][y] = -1;
            a[y][x] = 1;
        }
        memset(size, -1, sizeof size);
        dfs(0);
        int ans = 0;
        for(i = 0; i < n; i++)
            ans = (ans + f[0][i]) % P;
        printf("Case #%d: %d\n", i0, ans);
    }
    return 0;
}
*/
