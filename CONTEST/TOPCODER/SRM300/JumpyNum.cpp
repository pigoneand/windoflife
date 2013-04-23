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

int f[20][2][2][10];
bool caled[20][2][2][10];

class JumpyNum
{
public:
    
    int getWays(const string& s, int offset, bool couldExt, bool considerDelta, int lastDigit)
    {
        if (caled[offset][couldExt][considerDelta][lastDigit])
            return f[offset][couldExt][considerDelta][lastDigit];
        caled[offset][couldExt][considerDelta][lastDigit] = true;
        
        int& ret = f[offset][couldExt][considerDelta][lastDigit];
        if (offset == s.length()) return ret = 1;
        
        ret = 0;
        for (int d = 0; d <= 9; ++d)
        {
            if (!couldExt && d > s[offset] - '0') continue;
            if (considerDelta && abs(lastDigit - d) < 2) continue;
            ret += getWays(s, offset + 1, couldExt || (d < s[offset] - '0'), considerDelta || (d > 0), d);
        }
        return ret;
    }
    
    int getAns(int upper)
    {
        ostringstream ostr;
        ostr << upper;
        string s = ostr.str();
        
        memset(caled, false, sizeof(caled));
        return getWays(s, 0, false, false, 0);
    }
    
    int howMany(int low, int high)
    {
        int ans1 = getAns(high);
        int ans2 = getAns(low - 1);
        return ans1 - ans2;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 10; int Arg2 = 9; verify_case(0, Arg2, howMany(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 9; int Arg1 = 23; int Arg2 = 9; verify_case(1, Arg2, howMany(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 2000000000; int Arg1 = 2000000000; int Arg2 = 0; verify_case(2, Arg2, howMany(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 8000; int Arg1 = 20934; int Arg2 = 3766; verify_case(3, Arg2, howMany(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    JumpyNum ___test;
    ___test.run_test(-1);
}
// END CUT HERE
