//BEGIN CUT HERE
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <string.h>
#include <sstream>
#include <queue>
using namespace std;

//END CUT HERE

class CageTheMonster
{
public:
    vector<string> lab;
    int N, M;
    int r1, r2, c1, c2;
    bool visit[51][51];
    bool isOK(int x, int y)
    {
        int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        
        memset(visit, false, sizeof(visit));
        visit[x][y] = true;
        queue<pair<int, int> > q;
        q.push(make_pair(x, y));
        
        while (q.size() > 0)
        {
            pair<int, int> now = q.front();
            q.pop();
            int nx = now.first;
            int ny = now.second;
            if (nx == 0 || nx == N - 1 || ny == 0 || ny == M - 1) return false;
            
            for (int k = 0; k < 4; ++k)
            {
                int nnx = nx + dir[k][0];
                int nny = ny + dir[k][1];
                if (nnx >= 0 && nnx < N && nny >= 0 && nny < M)
                    if (!visit[nnx][nny] && lab[nnx][nny] != '#')
                        if (nnx != r1 && nnx != r2 && nny != c1 && nny != c2)
                        {
                            visit[nnx][nny] = true;
                            q.push(make_pair(nnx, nny));
                        }
            }
        }
        return true;
    }
    
    int capture(vector <string> labyrinth)
    {
        lab = labyrinth;
        N = (int) lab.size();
        M = (int) lab[0].size();
        
        int ans = 10;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (lab[i][j] == '^')
                {
                    for (int s = 0; s < 16; ++s)
                    {
                        r1 = r2 = c1 = c2 = -1;
                        int cnt = 0;
                        if (s & (1 << 0)) { r1 = i - 1; cnt++; }
                        if (s & (1 << 1)) { r2 = i + 1; cnt++; }
                        if (s & (1 << 2)) { c1 = j - 1; cnt++; }
                        if (s & (1 << 3)) { c2 = j + 1; cnt++; }
                        if (isOK(i, j)) ans = min(ans, cnt);
                    }
                }
        
        return ans == 10 ? -1 : ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {
        ".######..",
        ".#^^^^#..",
        ".#^^^^#..",
        ".#^^^^#..",
        ".##^^##..",
        "...^^...."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, capture(Arg0)); }
	void test_case_1() { string Arr0[] = {
        ".....",
        ".^#^.",
        ".#^#.",
        "..#.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, capture(Arg0)); }
	void test_case_2() { string Arr0[] = {
        "#....",
        "^#...",
        "#...."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(2, Arg1, capture(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    CageTheMonster ___test;
    ___test.run_test(-1);
} 
// END CUT HERE 
