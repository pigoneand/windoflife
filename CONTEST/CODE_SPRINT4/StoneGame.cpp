#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

long long MOD = 1000000007;

class DefectiveAddition
{
public:
    int count(vector<int> cards, int n)
    {
        int N = (int) cards.size(),i,j;
        sort(cards.begin(), cards.end());
        
        int t = 1;
        while (2*t <= cards[N-1]+1) {
            t *= 2;
        }
        if (n >= 2*t) {
            return 0;
        }
        
        long long dp[102][2];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for(i=0;i<N-1;i++) {
            for(j=0;j<2;j++) {
                dp[i+1][j] += dp[i][j] * min(cards[i]+1, t);
                dp[i+1][j] %= MOD;
                
                dp[i+1][j^1] += dp[i][j] * max(cards[i] - t + 1, 0);
                dp[i+1][j^1] %= MOD;
            }
        }
        long ans = 0;
        if (n >= 0 && n < t) {
            ans = dp[N-1][0];
        } else {
            ans = dp[N-1][1];
        }
        
        if(cards[N-1] >= t) {
            vector<int> ncards = cards;
            ncards[N-1] -= t;
            ans = (ans + count(ncards, (n^t) ) ) % MOD;
        }
        
        return (int)ans;
    }
};

int main()
{
    int N;
    cin >> N;
    vector<int> stones(N);
    
    for (int i = 0; i < N; ++i)
        cin >> stones[i];
    
    DefectiveAddition da;
    long long ans1 = da.count(stones, 0);

    for (int i = 0; i < N; ++i)
        stones[i]--;
    long long ans2 = da.count(stones, 0);
    
    long long ans = (ans1 - ans2 + MOD) % MOD;
    
    cout << ans << endl;
    
    return 0;
}