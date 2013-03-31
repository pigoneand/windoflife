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
using namespace std;
//END CUT HERE

class PowerDigit
{
public:
    int digitK(int x, int y, int k)
    {
        bool exceed = false;
        long long ans = 1;
        for (int i = 0; i < y; ++i)
        {
            ans = ans * x;
            if (ans >= 100000) exceed = true;
            ans %= 100000;
        }
        
        ostringstream ostr;
        ostr << ans;
        string ansStr = ostr.str();
        if (k + 1 > ansStr.length() && !exceed) return -1;
        while (ansStr.length() < k + 1) ansStr = string(1, '0') + ansStr;
        return (int) (ansStr[ansStr.length() - 1 - k] - '0');
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 10; int Arg2 = 1; int Arg3 = 2; verify_case(0, Arg3, digitK(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 10; int Arg2 = 4; int Arg3 = -1; verify_case(1, Arg3, digitK(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 1000; int Arg2 = 0; int Arg3 = 6; verify_case(2, Arg3, digitK(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 9999; int Arg1 = 10000; int Arg2 = 4; int Arg3 = 0; verify_case(3, Arg3, digitK(Arg0, Arg1, Arg2)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    PowerDigit ___test;
    ___test.run_test(-1);
}
// END CUT HERE
