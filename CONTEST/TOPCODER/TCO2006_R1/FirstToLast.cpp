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

class FirstToLast
{
public:
    int getSmallest(int p, int q)
    {
        for (int i = 2; i <= 100; ++i)
            if (p % i == 0 && q % i == 0)
                p /= i, q /= i;
        if (p == 1 && q == 1) return 1;
        if (p == 1 && q == 10) return 10;
        if (p == 1 && q == 100) return 100;
        if (p == q) return 1;
        if (p == 10 && q == 100) return 10;
        if (p >= 10 * q) return -1;

        long long pow[20];
        pow[0] = 1;
        for (int i = 1; i < 20; ++i) pow[i] = pow[i - 1] * 10;
        
        for (int n = 2; n <= 10; ++n)
        {
            long long now = pow[n - 1] * p - q;
            long long another = 10 * q - p;
            for (long long a1 = 1; a1 <= 9; ++a1)
            {
                if (now * a1 % another == 0)
                {
                    long long a2n = now * a1 / another;
                    long long ans = a1 * pow[n - 1] + a2n;
                    if (a2n >= pow[n - 1]) continue;
                    if (ans <= 2000000000LL) return (int) ans;
                }
            }
        }
        return -1;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; verify_case(0, Arg2, getSmallest(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 4; int Arg2 = 102564; verify_case(1, Arg2, getSmallest(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 6; int Arg2 = -1; verify_case(2, Arg2, getSmallest(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 1; int Arg1 = 100; int Arg2 = 100; verify_case(3, Arg2, getSmallest(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 92; int Arg1 = 10; int Arg2 = -1; verify_case(4, Arg2, getSmallest(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    FirstToLast ___test;
    ___test.run_test(-1);
}
// END CUT HERE
