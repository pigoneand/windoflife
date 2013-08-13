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
using namespace std;
//END CUT HERE

class EscapingJail
{
public:
    int getDis(char c)
    {
        if (c == ' ') return 999999;
        if (islower(c)) return c - 'a' + 10;
        if (isupper(c)) return c - 'A' + 36;
        return c - '0';
    }
    
    int getMaxDistance(vector <string> chain)
    {
        int N = (int) chain.size();
        vector<vector<int> > dis(N, vector<int>(N, 0));
        
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                dis[i][j] = getDis(chain[i][j]);
        
        for (int k = 0; k < N; ++k)
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        
        int ans = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                ans = max(ans, dis[i][j]);
        if (ans == 999999) ans = -1;
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0568",
        "5094",
        "6903",
        "8430"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(0, Arg1, getMaxDistance(Arg0)); }
	void test_case_1() { string Arr0[] = {"0 ",
        " 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, getMaxDistance(Arg0)); }
	void test_case_2() { string Arr0[] = {"0AxHH190",
        "A00f3AAA",
        "x00     ",
        "Hf 0  x ",
        "H3  0   ",
        "1A   0  ",
        "9A x  0Z",
        "0A    Z0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 43; verify_case(2, Arg1, getMaxDistance(Arg0)); }
	void test_case_3() { string Arr0[] = {"00",
        "00"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, getMaxDistance(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    EscapingJail ___test;
    ___test.run_test(-1);
}
// END CUT HERE
