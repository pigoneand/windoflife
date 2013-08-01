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
#include <numeric>
#include <functional>
#include <queue>
using namespace std;
//END CUT HERE

class SysFailure
{
public:
    
    vector<int> getComSizes(const vector<string>& s)
    {
        int H = (int) s.size();
        int W = (int) s[0].size();
        vector<int> ret;
        
        vector<vector<bool> > visit(H, vector<bool>(W, false));
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                if (s[i][j] == '1' && !visit[i][j])
                {
                    queue<pair<int, int> > q;
                    q.push(make_pair(i, j));
                    visit[i][j] = true;
                    int curSize = 0;
                    
                    while (q.size() > 0)
                    {
                        curSize++;
                        pair<int, int> now = q.front();
                        q.pop();
                        
                        for (int dx = -1; dx <= 1; ++dx)
                        {
                            for (int dy = -1; dy <= 1; ++dy)
                            {
                                int nx = dx + now.first;
                                int ny = dy + now.second;
                                if (nx >= 0 && nx < H && ny >= 0 && ny < W && visit[nx][ny] == false && s[nx][ny] == '1')
                                {
                                    visit[nx][ny] = true;
                                    q.push(make_pair(nx, ny));
                                }
                            }
                        }
                    }
                    ret.push_back(curSize);
                }
        return ret;
    }
    
    bool isCritical(const vector<string>& s, int n)
    {
        vector<int> ss = getComSizes(s);
        for (int i = 0; i < ss.size(); ++i)
            if (ss[i] >= n) return false;
        return true;
    }
    
    int critical(int n, vector <string> state)
    {
        if (isCritical(state, n)) return -1;
        int ans = 0;
        for (int i = 0; i < state.size(); ++i)
            for (int j = 0; j < state[0].size(); ++j)
                if (state[i][j] == '1')
                {
                    state[i][j] = '0';
                    if (isCritical(state, n)) ans++;
                    state[i][j] = '1';
                }
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; string Arr1[] = { "00000",
        "00000",
        "11111" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, critical(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 6; string Arr1[] = { "01010",
        "10001",
        "11011",
        "10001",
        "01010"} ; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, critical(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 4; string Arr1[] = { "111",
        "111" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, critical(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 2; string Arr1[] = { "101" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(3, Arg2, critical(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    SysFailure ___test;
    ___test.run_test(-1);
}
// END CUT HERE
