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

class RandomizedQuickSort
{
public:
    map<int, double> f;
    
    double getF(int L, int S, int a, int b)
    {
        if (L <= S) return b * L * L;
        if (f.count(L) > 0) return f[L];
        
        double & ret = f[L];
        ret = a * L;
        for (int l = 0; l < L; ++l)
            ret += 1.0 / L * (getF(l, S, a, b) + getF(L - l - 1, S, a, b));
        return ret;
    }
    
    double getExpectedTime(int listSize, int S, int a, int b)
    {
        f.clear();
        return getF(listSize, S, a, b);
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; double Arg4 = 1.0; verify_case(0, Arg4, getExpectedTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; double Arg4 = 3.0; verify_case(1, Arg4, getExpectedTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; double Arg4 = 5.666666666666667; verify_case(2, Arg4, getExpectedTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 1; int Arg3 = 10; double Arg4 = 17.666666666666668; verify_case(3, Arg4, getExpectedTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 10; int Arg1 = 5; int Arg2 = 3; int Arg3 = 2; double Arg4 = 112.37380952380951; verify_case(4, Arg4, getExpectedTime(Arg0, Arg1, Arg2, Arg3)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    RandomizedQuickSort ___test;
    ___test.run_test(-1);
}
// END CUT HERE
