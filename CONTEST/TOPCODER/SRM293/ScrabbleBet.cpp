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

class ScrabbleBet
{
public:
    double estimate(int trials, int games, int winsNeeded, int winChance)
    {
        double p = 1.0 * winChance / 100;
        
        double C[30][30];
        memset(C, 0, sizeof(C));
        C[0][0] = 1;
        
        for (int i = 1; i <= games; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                C[i][j] = 0;
                if (j > 0) C[i][j] += C[i - 1][j - 1] * p;
                C[i][j] += C[i - 1][j] * (1 - p);
            }
        }
        
        double winP = 0;
        for (int i = winsNeeded; i <= games; ++i) winP += C[games][i];
    
        double ansP = 1;
        for (int i = 1; i <= trials; ++i) ansP = ansP * (1 - winP);
        ansP = 1 - ansP;
        
        return ansP;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 1; int Arg3 = 50; double Arg4 = 0.9375; verify_case(0, Arg4, estimate(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 50; double Arg4 = 0.4375; verify_case(1, Arg4, estimate(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 10; int Arg2 = 5; int Arg3 = 25; double Arg4 = 0.5566860567603682; verify_case(2, Arg4, estimate(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 2; int Arg1 = 20; int Arg2 = 5; int Arg3 = 10; double Arg4 = 0.08448495352665641; verify_case(3, Arg4, estimate(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 50; int Arg1 = 15; int Arg2 = 1; int Arg3 = 0; double Arg4 = 0.0; verify_case(4, Arg4, estimate(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arg0 = 50; int Arg1 = 17; int Arg2 = 16; int Arg3 = 100; double Arg4 = 1.0; verify_case(5, Arg4, estimate(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_6() { int Arg0 = 50; int Arg1 = 10; int Arg2 = 10; int Arg3 = 75; double Arg4 = 0.9448701546682944; verify_case(6, Arg4, estimate(Arg0, Arg1, Arg2, Arg3)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    ScrabbleBet ___test;
    ___test.run_test(-1);
}
// END CUT HERE
